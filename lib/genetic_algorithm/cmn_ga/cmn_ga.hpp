/*
 * cmn_ga.hpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_CMN_GA_CMN_GA_HPP_
#define LIB_GENETIC_ALGORITHM_CMN_GA_CMN_GA_HPP_

#include <cstddef>
#include <limits>
#include <vector>
#include <valarray>
#include <random>
#include <utility>
#include <bits/stl_function.h>


#include "../../../lib/utility/stlmath.hpp"
#include "../../../lib/utility/valarray.hpp"
#include "../../../lib/utility/vector.hpp"
#include "../../../lib/algorithm/quick_select.hpp"
#include "../../../lib/algorithm/binary_search.hpp"
#include "../../../lib/algorithm/minmax.hpp"
#include "../../../lib/algorithm/once.hpp"
#include "../common/space.hpp"
#include "../common/generating/uniform_generator.hpp"
#include "../common/coding/gray_coder.hpp"
#include "../common/coding/numeric_coder.hpp"


namespace genetic_algorithm {
namespace cmn_ga {

struct cmn_ga {
    typedef unsigned long uint_type;
    typedef double        real_type;
    typedef std::vector<bool>      gcode_type;
    typedef std::valarray<uint_type> icode_type;
    typedef std::valarray<real_type> point_type;
    typedef std::size_t size_type;
    typedef std::valarray<size_type> indices_type;
    typedef std::valarray<bool> mask_type;

    static constexpr real_type exponential_scaling_function_median_value = 0.5;
    static constexpr real_type local_convergence_criteria = 1e+10;

    struct parameters {
        std::size_t
            initial_population_size,
            crossover_pair_number,
            mutated_individuals_number,
            nearest_individuals_number,
            crowd_size,
            max_try_number,
            max_population_size,
            precision;
    };

    const parameters params;

    ::genetic_algorithm::common::coding::numeric_coder<real_type, uint_type> ncoder;

    std::valarray<real_type> fitness;
    real_type min_fitness, max_fitness;
    std::vector<point_type> points;
    std::vector<icode_type> icodes;
    std::vector<std::vector<real_type>> proximity_matrix;

    std::size_t population_size;

    std::function<real_type(const real_type fitness)> threshold;
    std::function<real_type(const point_type, const point_type)> distance;
    std::function<real_type(const point_type)> fitness_function;
    ::genetic_algorithm::common::real_space<real_type> real_space;
    ::genetic_algorithm::common::uint_space<uint_type> uint_space;

    mutable std::mt19937_64 engine;

    cmn_ga(
            const parameters& params,
            ::genetic_algorithm::common::real_space<real_type>& realSpace,
            ::genetic_algorithm::common::uint_space<uint_type>& uintSpace,
             std::function<real_type(const point_type)> fitnessFunction) :
                params (params),
                real_space (realSpace),
                uint_space (uintSpace),
                ncoder (realSpace, uintSpace),
                fitness_function (fitnessFunction),
                population_size (),
                fitness (),
                min_fitness (),
                max_fitness (),
                points (),
                icodes (),
                proximity_matrix ()
    {}

    void init() {
        ncoder = ::genetic_algorithm::common::coding::numeric_coder<real_type, uint_type>(real_space, uint_space);

        namespace g = ::genetic_algorithm::common::generating;
        g::uniform_generator<uint_type> gen = g::uniform_generator<uint_type>(uint_space, engine);
        std::vector<icode_type> initialICodes = gen(params.initial_population_size);

        min_fitness = std::numeric_limits<real_type>::max();
        max_fitness = std::numeric_limits<real_type>::lowest();

        for (population_size = 0; population_size < params.initial_population_size; ++population_size) {
            icodes[population_size] = std::move(initialICodes[population_size]);
            points[population_size] = ncoder.to_real(icodes[population_size]);
            fitness[population_size] = fitness_function(points[population_size]);
            if (min_fitness > fitness[population_size])
                min_fitness = fitness[population_size];
            if (max_fitness < fitness[population_size])
                max_fitness = fitness[population_size];
        }

        for (size_type i = 0; i < population_size; ++i) {
            for (size_type j = 0; j <= i; ++j) {
                proximity_matrix[i][j] = 1.0 / distance(points[i], points[j]);
            }
        }
    }

    auto operator() () -> std::vector<point_type> {
        indices_type localOptimas;
        while ( true ) {
            localOptimas = local_optimas();
            std::valarray<real_type> scaledFitness = scale_fitness(localOptimas);
            if (max_population_reached() || local_convergence(localOptimas).min())
                break;
            next_generation(scaledFitness);
        }
        std::vector<point_type> optimaPoints (localOptimas.size());
        for (size_type optimaIndex = 0; optimaIndex < localOptimas.size(); ++optimaIndex)
            optimaPoints[optimaIndex] = points[optimaIndex];
        return optimaPoints;
    }

    auto local_convergence(const indices_type optimaIndices) const -> mask_type {
        mask_type converged (false, optimaIndices.size());
        for (size_type optimaIndex = 0; optimaIndex < optimaIndices.size(); ++optimaIndex) {
            for (size_type k = 0; !converged[optimaIndex] && k < population_size; ++k) {
                converged[optimaIndex] = local_convergence_criteria < proximity(optimaIndex, k);
            }
        }
        return converged;
    }
    auto max_population_reached() const -> bool {
        return population_size >= params.max_population_size * 0.97;
    }

    void next_generation(const std::valarray<real_type>& scaledFitness) {
        //-- crossover --
        indices_type p1, p2;
        std::tie(p1, p2) = selection(scaledFitness);
        size_type pairIndex, tryNumber = 0;
        algorithm::once<false> pairIndexOnce(params.crossover_pair_number);
        while (tryNumber < params.max_try_number && pairIndexOnce) {
            pairIndex = pairIndexOnce();
            icode_type derivedICode = crossover(p1[pairIndex], p2[pairIndex]);
            if (!addition(derivedICode, scaledFitness, population_size + pairIndexOnce.used_number()))
                pairIndexOnce.unuse(pairIndex);
            ++tryNumber;
        }

        //-- mutation --
        std::uniform_int_distribution<size_type> dist (0, population_size);
        tryNumber = 0;
        size_type mutationNumber = 0;
        while (tryNumber < params.max_try_number && mutationNumber < params.mutated_individuals_number) {
            size_type mutationIndex = dist(engine);
            icode_type mutantICode = mutation(mutationIndex);
            if ( uint_space.is_in(mutantICode) &&
                    addition(mutantICode, scaledFitness, population_size + pairIndexOnce.used_number() + mutationNumber))
                ++mutationNumber;
            ++tryNumber;
        }
        population_size = population_size + pairIndexOnce.used_number() + mutationNumber;
    }

    auto addition(const icode_type& icode, const std::valarray<real_type>& scaledFitness, const size_type index) -> bool {
        point_type point = ncoder.to_real(icode);
        std::vector<real_type> proximitiesVector (population_size);
        real_type nearestIndex = 0;
        for (size_type k = 0; k < population_size; ++k) {
            proximitiesVector[k] = 1.0 / distance(point, points[k]);
            if (proximitiesVector[nearestIndex] < proximitiesVector[k])
                nearestIndex = k;
        }
        register real_type thresholdRMin = threshold(scaledFitness[nearestIndex]);
        bool success = true;
        if (thresholdRMin < proximitiesVector[nearestIndex])
            success = false;
        else {
            fitness[index] = fitness_function(point);
            icodes [index] = std::move(icode);
            points [index] = std::move(point);
            proximity_matrix[index] = std::move(proximitiesVector);
        }
        return success;
    }

    auto mutation(const size_type index) const -> icode_type {
        icode_type mutant (uint_space.size());
        for (size_type dim = 0; dim < uint_space.size(); ++dim) {
            double mean = icodes[index][dim];
            double stddev = uint_space.right_bounds()[dim] / (2.0 * 3.0);
            mutant[dim] = uint_type(utility::stlmath::round<real_type>()(std::normal_distribution<real_type>( mean, stddev )(engine)));
        }
        return mutant;
    }

    auto crossover(const size_type p1, const size_type p2) const -> icode_type {
        icode_type derived (uint_space.size());
        for (size_type dim = 0; dim < uint_space.size(); ++dim) {
            uint_type a, b;
            std::tie(a, b) = std::minmax(icodes[p1][dim], icodes[p2][dim]);
            derived[dim] = std::uniform_int_distribution<uint_type>(a, b)(engine);
        }
        return derived;
    }
    auto selection(const std::valarray<real_type>& scaledFitness) const -> std::pair<indices_type, indices_type> {
        indices_type p1 = proportionate_selection(scaledFitness, params.crossover_pair_number);
        indices_type p2 (params.crossover_pair_number);
        for (size_type p1Index = 0; p1Index < params.crossover_pair_number; ++p1Index) {
            std::valarray<real_type> proximitiesVector = proximities(p1[p1Index]);
            indices_type crowd = proportionate_selection(proximitiesVector, params.crowd_size);
            std::valarray<real_type> crowdFitness = scaledFitness[crowd];
            size_type crowdFittestIndex = algorithm::max<real_type>()(crowdFitness);
            p2[p1Index] = crowd[crowdFittestIndex];
        }
        return std::make_pair(p1, p2);
    }
    auto proportionate_selection(const std::valarray<real_type>& proportions, const size_type selectedNumber) const -> indices_type {
        register real_type proportionsSum = proportions.sum();
        std::uniform_real_distribution<real_type> dist (0, proportionsSum);
        std::valarray<real_type> roulette = utility::valarray::cumulative_sum(proportions / proportionsSum);

        register size_type selectedIndex = 0;
        indices_type selected (params.crossover_pair_number);

        for (size_type k = 0; k < params.crossover_pair_number; ++k) {
            size_type roll = dist(engine);
            size_type rollIndex = algorithm::binary_search<real_type>()(roulette, roll);
            selected[selectedIndex++] = rollIndex;
        }

        return selected;
    }


    auto scale_fitness(const indices_type& localOptimas) const -> std::valarray<real_type> {
        std::vector<std::valarray<real_type>> relativeFitnesses;
        relativeFitnesses.reserve(localOptimas.size());

        for (const auto optimaIndex : localOptimas) {
            std::valarray<real_type> relativeFitness (population_size);
            register real_type diffFitness = fitness[optimaIndex] - min_fitness;
            for (size_type k = 0; k < population_size; ++k)
                relativeFitness[k] = (fitness[k] - min_fitness) / diffFitness;

            size_type medianIndex = algorithm::quick_select<size_type>()(relativeFitness, (population_size + 1) / 2);

            using utility::stlmath::ln;
            double exponentialScaleFactor = ln<real_type>()(exponential_scaling_function_median_value) / ln<real_type>()(relativeFitness[medianIndex]);
            relativeFitness = std::pow(relativeFitness, exponentialScaleFactor);
            relativeFitnesses.push_back(std::move(relativeFitness));
        }
        std::valarray<real_type> scaledFitness (population_size);
        for (size_type k = 0; k < population_size; ++k) {
            register real_type proximitySum = 0, proximitySumWeighted = 0;
            for (size_type i = 0; i < localOptimas.size(); ++i) {
                proximitySum += proximity(i, k);
                proximitySumWeighted += proximity(i, k) * relativeFitnesses[i][k];
            }
            scaledFitness[k] = proximitySumWeighted / proximitySum;
        }
        return scaledFitness;
    }

    auto local_optimas() const -> indices_type {
        std::vector<size_type> localOptimas;
        localOptimas.reserve(population_size / (params.nearest_individuals_number / 2));
        for(size_type k = 0; k < population_size; ++k) {
            indices_type nearestNeighbours = nearest_neighbours(k);
            std::valarray<bool> cmp = fitness[k] > fitness[nearestNeighbours];
            bool isLocalOptima = utility::valarray::reduce(std::logical_and<bool>(), cmp);
            if (isLocalOptima)
                localOptimas.push_back(k);
        }
        return utility::valarray::from(localOptimas);
    }

    auto nearest_neighbours(const size_type index) const -> indices_type {
        size_type rank = population_size - params.nearest_individuals_number - 1;
        std::valarray<real_type> inverseDistancesVector = proximities(index);
        register size_type rankIndex = algorithm::quick_select<size_type>()(inverseDistancesVector, rank);
        register size_type rankValue = inverseDistancesVector[rankIndex];
        size_type nearestIndex = 0;
        indices_type nearest (params.nearest_individuals_number);
        for (size_type k = 0; k < population_size; ++k)
            if (inverseDistancesVector[k] > rankValue)
                nearest[nearestIndex++] = k;
        return nearest;
    }

    auto proximities(const size_type index) const -> std::valarray<real_type> {
        std::valarray<real_type> inverseDistancesVector (population_size);
        for (size_type j = 0; j < index; ++j)
            inverseDistancesVector[j] = proximity_matrix[index][j];
        //inverse_distances_vector[index][index] = std::numeric_limits<double>::infinity();
        for (size_type i = index + 1; i < population_size; ++i)
            inverseDistancesVector[i] = proximity_matrix[i][index];
        return inverseDistancesVector;
    }
    auto proximity(size_type i, size_type j) const -> real_type {
        if (i < j)
            std::swap(i, j);
        return proximity_matrix[i][j];
    }
};

}   //-- namespace cmn_ga --
}   //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_CMN_GA_CMN_GA_HPP_ */
