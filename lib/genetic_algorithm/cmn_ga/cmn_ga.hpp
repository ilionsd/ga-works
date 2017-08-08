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
#include "../common/generating/uniform_generator.hpp"
#include "../common/coding/gray_coder.hpp"
#include "../common/coding/numeric_coder.hpp"


namespace genetic_algorithm {
namespace cmn_ga {

struct cmn_ga {
    typedef std::size_t nm_type;
    typedef double      fp_type;
    typedef std::vector<bool>      gcode_type;
    typedef std::valarray<nm_type> ncode_type;
    typedef std::valarray<fp_type> point_type;
    typedef std::size_t size_type;
    typedef std::valarray<size_type> indices_type;
    typedef std::valarray<bool> mask_type;

    static constexpr fp_type exponential_scaling_function_median_value = 0.5;
    static constexpr fp_type local_convergence_criteria = 1e+10;

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

    ::genetic_algorithm::common::coding::numeric_coder<fp_type, nm_type> ncoder;

    std::valarray<fp_type> fitness;
    fp_type min_fitness, max_fitness;
    std::vector<point_type> points;
    std::vector<ncode_type> ncodes;
    std::vector<std::vector<fp_type>> proximity_matrix;

    std::size_t population_size;

    std::function<fp_type(const fp_type fitness)> threshold;
    std::function<fp_type(const point_type, const point_type)> distance;
    std::function<fp_type(const point_type)> fitness_function;
    size_type space_size;

    mutable std::mt19937_64 gen;

    void init(const point_type& leftBounds, const point_type& rightBounds) {
        namespace g = ::genetic_algorithm::common::generating;
        g::uniform_generator<nm_type> gen = g::make_uniform(leftBounds.size(), leftBounds, rightBounds);
        std::vector<ncode_type> initialNCodes = gen(params.initial_population_size);

        min_fitness = std::numeric_limits<fp_type>::max();
        max_fitness = std::numeric_limits<fp_type>::lowest();

        for (population_size = 0; population_size < params.initial_population_size; ++population_size) {
            ncodes[population_size] = std::move(initialNCodes[population_size]);
            points[population_size] = ncoder.decode(ncodes[population_size]);
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

    auto operator() () -> std::valarray<point_type> {
        indices_type localOptimas;
        while ( true ) {
            localOptimas = local_optimas();
            std::valarray<fp_type> scaledFitness = scale_fitness(localOptimas);
            if (max_population_reached() || local_convergence(localOptimas).min())
                break;
            next_generation(scaledFitness);
        }

        return points[localOptimas];
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

    void next_generation(const std::valarray<fp_type>& scaledFitness) {
        indices_type p1, p2;
        std::tie(p1, p2) = selection(scaledFitness);
        size_type pairIndex, tryNumber = 0;
        algorithm::once pairIndexOnce(params.crossover_pair_number);
        while (tryNumber < params.max_try_number && pairIndexOnce) {
            pairIndex = pairIndexOnce();
            ncode_type derivedNCode = crossover(p1[pairIndex], p2[pairIndex]);
            if (!addition(derivedNCode, scaledFitness, population_size + pairIndexOnce.used_number()))
                pairIndexOnce.unuse(pairIndex);
            ++tryNumber;
        }

        std::uniform_int_distribution<size_type> dist (0, population_size);
        tryNumber = 0;
        size_type mutationNumber = 0;
        while (tryNumber < params.max_try_number && mutationNumber < params.mutated_individuals_number) {

        }
        population_size += pairIndexOnce.used_number();


    }

    auto addition(const ncode_type& ncode, const std::valarray<fp_type>& scaledFitness, const size_type index) -> bool {
        point_type point = ncoder.decode(ncode);
        std::vector<fp_type> proximitiesVector (population_size);
        fp_type nearestIndex = 0;
        for (size_type k = 0; k < population_size; ++k) {
            proximitiesVector[k] = 1.0 / distance(point, points[k]);
            if (proximitiesVector[nearestIndex] < proximitiesVector[k])
                nearestIndex = k;
        }
        register fp_type thresholdRMin = threshold(scaledFitness[nearestIndex]);
        bool success = true;
        if (thresholdRMin < proximitiesVector[nearestIndex])
            success = false;
        else {
            fitness[index] = fitness_function(point);
            ncodes [index] = std::move(ncode);
            points [index] = std::move(point);
            proximity_matrix[index] = std::move(proximitiesVector);
        }
        return success;
    }

    auto mutation(const size_type index) const {
        point_type mutant (space_size);
        for (size_type dim = 0; dim < space_size; ++dim) {
            double mean = points[dim];
            double stddev = 1;
            mutant[dim] = std::normal_distribution<fp_type>( mean, stddev )(gen);
        }
    }

    auto crossover(const size_type p1, const size_type p2) const -> ncode_type {
        ncode_type derived (space_size);
        for (size_type dim = 0; dim < space_size; ++dim) {
            derived[dim] = std::uniform_int_distribution<nm_type>(std::minmax(ncodes[p1][dim], ncodes[p2][dim]))(gen);
        }
        return derived;
    }
    auto selection(const std::valarray<fp_type>& scaledFitness) const -> std::pair<indices_type, indices_type> {
        indices_type p1 = proportionate_selection(scaledFitness, params.crossover_pair_number);
        indices_type p2 (params.crossover_pair_number);
        for (size_type p1Index = 0; p1Index < params.crossover_pair_number; ++p1Index) {
            std::valarray<fp_type> proximitiesVector = proximities(p1[p1Index]);
            indices_type crowd = proportionate_selection(proximitiesVector, params.crowd_size);
            std::valarray<fp_type> crowdFitness = scaledFitness[crowd];
            size_type crowdFittestIndex = algorithm::max()(crowdFitness);
            p2[p1Index] = crowd[crowdFittestIndex];
        }
        return std::make_pair(p1, p2);
    }
    auto proportionate_selection(const std::valarray<fp_type>& proportions, const size_type selectedNumber) const -> indices_type {
        register fp_type proportionsSum = proportions.sum();
        std::uniform_real_distribution<fp_type> dist (0, proportionsSum);
        std::valarray<fp_type> roulette = utility::valarray::cumulative_sum(proportions / proportionsSum);

        register size_type selectedIndex = 0;
        indices_type selected (params.crossover_pair_number);

        for (size_type k = 0; k < params.crossover_pair_number; ++k) {
            size_type roll = dist(gen);
            size_type rollIndex = algorithm::binary_search()(roulette, roll);
            selected[selectedIndex++] = rollIndex;
        }

        return selected;
    }


    auto scale_fitness(const indices_type& localOptimas) const -> std::valarray<fp_type> {
        std::vector<std::valarray<fp_type>> relativeFitnesses;
        relativeFitnesses.reserve(localOptimas.size());

        for (const auto optimaIndex : localOptimas) {
            std::valarray<fp_type> relativeFitness (population_size);
            register fp_type diffFitness = fitness[optimaIndex] - min_fitness;
            for (size_type k = 0; k < population_size; ++k)
                relativeFitness[k] = (fitness[k] - min_fitness) / diffFitness;

            size_type medianIndex = algorithm::quick_select()(relativeFitness, (population_size + 1) / 2);

            using utility::stlmath::ln;
            double exponentialScaleFactor = ln<fp_type>()(exponential_scaling_function_median_value) / ln<fp_type>()(relativeFitness[medianIndex]);
            relativeFitness = std::pow(relativeFitness, exponentialScaleFactor);
            relativeFitnesses.push_back(std::move(relativeFitness));
        }
        std::valarray<fp_type> scaledFitness (population_size);
        for (size_type k = 0; k < population_size; ++k) {
            register fp_type proximitySum = 0, proximitySumWeighted = 0;
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
        std::valarray<fp_type> inverseDistancesVector = proximities(index);
        register size_type rankIndex = algorithm::quick_select()(inverseDistancesVector, rank);
        register size_type rankValue = inverseDistancesVector[rankIndex];
        size_type nearestIndex = 0;
        indices_type nearest (params.nearest_individuals_number);
        for (size_type k = 0; k < population_size; ++k)
            if (inverseDistancesVector[k] > rankValue)
                nearest[nearestIndex++] = k;
        return nearest;
    }

    auto proximities(const size_type index) const -> std::valarray<fp_type> {
        std::valarray<fp_type> inverseDistancesVector (population_size);
        for (size_type j = 0; j < index; ++j)
            inverseDistancesVector[j] = proximity_matrix[index][j];
        //inverse_distances_vector[index][index] = std::numeric_limits<double>::infinity();
        for (size_type i = index + 1; i < population_size; ++i)
            inverseDistancesVector[i] = proximity_matrix[i][index];
        return inverseDistancesVector;
    }
    auto proximity(size_type i, size_type j) const -> fp_type {
        if (i < j)
            std::swap(i, j);
        return proximity_matrix[i][j];
    }
};

}   //-- namespace cmn_ga --
}   //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_CMN_GA_CMN_GA_HPP_ */
