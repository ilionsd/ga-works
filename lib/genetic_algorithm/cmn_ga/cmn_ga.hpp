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


#include "../../../include/fn/math.hpp"
#include "../../../lib/utility/valarray.hpp"
#include "../../../lib/utility/vector.hpp"
#include "../../../lib/utility/assign_if.hpp"
#include "../../../lib/utility/math/euclidean_distance.hpp"
#include "../../../lib/algorithm/quick_select.hpp"
#include "../../../lib/algorithm/binary_search.hpp"
#include "../../../lib/algorithm/minmax.hpp"
#include "../../../lib/algorithm/once.hpp"
#include "../common/space.hpp"
#include "../common/generating/uniform_generator.hpp"
#include "proximity.hpp"


namespace genetic_algorithm {
namespace cmn_ga {

namespace detail {

template<typename T, typename F, std::size_t... I>
inline auto vactorize_impl(F f, std::index_sequence<sizeof...(I)>) -> std::function<T(std::valarray<T>)> {
    return [f](const std::valarray<T>& x) -> T { return f(x[I]...); };
}

}

template<typename T, std::size_t N, typename F>
inline auto vectorize(F f) -> std::function<T(std::valarray<T>)> {
    return detail::vactorize_impl(f, std::make_index_sequence<N>());
}

template<typename T>
struct threshold {
    typedef T value_type;

    inline constexpr threshold(const value_type thresholdMultiplier) :
            threshold_multiplier(thresholdMultiplier)
    {}

    inline constexpr value_type operator() (const value_type val) const {
        return 12.5 / (1.001 - val * (1.0 - 0.5 * threshold_multiplier));
    }
    value_type threshold_multiplier;
};

struct cmn_ga {
    typedef double        real_type;
    typedef std::valarray<real_type> point_type;
    typedef std::size_t size_type;
    typedef std::valarray<size_type> indices_type;
    typedef std::valarray<bool> mask_type;

    static constexpr real_type local_convergence_criteria = 1e+10;

    static const std::function<real_type(point_type, point_type)> default_proximity;

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

    std::valarray<real_type> fitness;
    real_type min_fitness, max_fitness;
    std::vector<point_type> points;
    proximity_matrix<real_type> proximities;

    std::size_t generation_number;
    std::size_t population_size;

    std::function<real_type(const real_type fitness)> threshold_f;
    std::function<real_type(const point_type, const point_type)> proximity_f;
    std::function<real_type(const point_type)> fitness_f;
    ::genetic_algorithm::common::real_space<real_type> real_space;

    mutable std::mt19937_64 engine;

    cmn_ga(
            const parameters& params,
            ::genetic_algorithm::common::real_space<real_type>& realSpace,
             std::function<real_type(const point_type)> fitnessFunction) :
                params (params),
                real_space (realSpace),
                fitness_f (fitnessFunction),
                population_size (),
                generation_number (),
                fitness (),
                min_fitness (),
                max_fitness (),
                points (),
                proximities (),
                proximity_f(default_proximity)
    {}

    void init() {
        generation_number = 0;

        namespace g = ::genetic_algorithm::common::generating;
        g::uniform_generator<real_type> gen = g::uniform_generator<real_type>(real_space, engine);
        std::vector<point_type> initialPoints = gen(params.initial_population_size);

        min_fitness = std::numeric_limits<real_type>::max();
        max_fitness = std::numeric_limits<real_type>::lowest();

        points.resize(params.max_population_size);
        fitness.resize(params.max_population_size);
        for (population_size = 0; population_size < params.initial_population_size; ++population_size) {
            points[population_size] = std::move(initialPoints[population_size]);
            fitness[population_size] = fitness_f(points[population_size]);
            ::utility::assign_if_greater<real_type>()(min_fitness, fitness[population_size]);
            ::utility::assign_if_less   <real_type>()(max_fitness, fitness[population_size]);
        }

        proximities.reserve(params.max_population_size);
        for (size_type i = 0; i < population_size; ++i) {
            std::valarray<real_type> proximitiesVector (i);
            for (size_type j = 0; j < i; ++j)
                proximitiesVector[j] = proximity_f(points[i], points[j]);
            proximities.add_vector(std::move(proximitiesVector));
        }
    }

    auto operator() () -> std::vector<point_type> {
        using std::cout;
        using std::endl;

        cout << "GA started" << endl;

        indices_type localOptimas;
        real_type thresholdMultiplier = 1.0;
        while ( true ) {
            cout << "Generation: " << generation_number << endl;
            cout << "Population size: " << population_size << endl;

            localOptimas = local_optimas();
            std::valarray<real_type> scaledFitness = scale_fitness(localOptimas);
            if (max_population_reached() || local_convergence(localOptimas).min())
                break;
            threshold_f = threshold<real_type>(thresholdMultiplier);
            next_generation(scaledFitness);
            ++generation_number;
            thresholdMultiplier *= 0.9;
        }
        cout << "GA finished" << endl;
        std::vector<point_type> optimaPoints (localOptimas.size());
        for (size_type optimaIndex = 0; optimaIndex < localOptimas.size(); ++optimaIndex)
            optimaPoints[optimaIndex] = points[optimaIndex];
        return optimaPoints;
    }

    auto local_convergence(const indices_type& localOptimas) const -> mask_type {
        mask_type converged (false, localOptimas.size());
        for (size_type optimaNumber = 0; optimaNumber < localOptimas.size(); ++optimaNumber) {
            for (size_type k = 0; !converged[optimaNumber] && k < population_size; ++k) {
                if (localOptimas[optimaNumber] != k)
                    converged[optimaNumber] = converged[optimaNumber] || local_convergence_criteria < proximities(localOptimas[optimaNumber], k);
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
            point_type derivedPoint = crossover(p1[pairIndex], p2[pairIndex]);
            if (addition(derivedPoint, scaledFitness, population_size + pairIndexOnce.used_number()))
                pairIndexOnce.use(pairIndex);
            ++tryNumber;
        }

        //-- mutation --
        std::uniform_int_distribution<size_type> dist (0, population_size);
        tryNumber = 0;
        size_type mutationNumber = 0;
        while (tryNumber < params.max_try_number && mutationNumber < params.mutated_individuals_number) {
            size_type mutationIndex = dist(engine);
            point_type mutantPoint = mutation(mutationIndex);
            if ( real_space.is_in(mutantPoint) &&
                    addition(mutantPoint, scaledFitness, population_size + pairIndexOnce.used_number() + mutationNumber))
                ++mutationNumber;
            ++tryNumber;
        }

        size_type nextPopulationSize = population_size + pairIndexOnce.used_number() + mutationNumber;
        size_type addedMinFitnessIndex, addedMaxFitnessIndex;
        auto addedBeginIt = std::begin(fitness) + population_size;
        auto addedEndIt   = std::begin(fitness) + nextPopulationSize;
        std::tie(addedMinFitnessIndex, addedMaxFitnessIndex) = ::algorithm::minmax()(addedBeginIt, addedEndIt);
        ::utility::assign_if_greater<real_type>()(min_fitness, fitness[population_size + addedMinFitnessIndex]);
        ::utility::assign_if_less   <real_type>()(max_fitness, fitness[population_size + addedMaxFitnessIndex]);

        population_size = nextPopulationSize;
    }

    auto addition(const point_type& point, const std::valarray<real_type>& scaledFitness, const size_type index) -> bool {
        std::valarray<real_type> proximitiesVector (index);
        real_type nearestIndex = 0;
        for (size_type k = 0; k < population_size; ++k) {
            proximitiesVector[k] = proximity_f(point, points[k]);
            if (proximitiesVector[nearestIndex] < proximitiesVector[k])
                nearestIndex = k;
        }
        for (size_type k = population_size; k < index; ++k)
            proximitiesVector[k] = proximity_f(point, points[k]);
        real_type thresholdProximity = threshold_f(scaledFitness[nearestIndex]);
        bool success = true;
        if (thresholdProximity < proximitiesVector[nearestIndex])
            success = false;
        else {
            fitness[index] = fitness_f(point);
            points [index] = std::move(point);
            proximities.add_vector(std::move(proximitiesVector));
        }
        return success;
    }

    auto mutation(const size_type index) const -> point_type {
        point_type mutant (real_space.size());
        for (size_type dim = 0; dim < real_space.size(); ++dim) {
            double mean = points[index][dim];
            double stddev = (real_space.right_bounds()[dim] - real_space.left_bounds()[dim]) / (2.0 * 3.0);
            mutant[dim] = std::normal_distribution<real_type>( mean, stddev )(engine);
        }
        return mutant;
    }

    auto crossover(const size_type p1, const size_type p2) const -> point_type {
        point_type derived (real_space.size());
        real_type a, b;
        for (size_type dim = 0; dim < real_space.size(); ++dim) {
            std::tie(a, b) = std::minmax(points[p1][dim], points[p2][dim]);
            derived[dim] = std::uniform_real_distribution<real_type>(a, b)(engine);
        }
        return derived;
    }
    auto selection(const std::valarray<real_type>& scaledFitness) const -> std::pair<indices_type, indices_type> {
        indices_type p1 = proportionate_selection(scaledFitness, params.crossover_pair_number);
        indices_type p2 (params.crossover_pair_number);
        for (size_type p1Index = 0; p1Index < params.crossover_pair_number; ++p1Index) {
            std::valarray<real_type> proximitiesVector = proximities.vector(p1[p1Index], false);
            indices_type crowd = proportionate_selection(proximitiesVector, params.crowd_size);
            std::valarray<real_type> crowdFitness = scaledFitness[crowd];
            size_type crowdFittestIndex = algorithm::max()(crowdFitness);
            p2[p1Index] = crowd[crowdFittestIndex];
        }
        return std::make_pair(p1, p2);
    }
    auto proportionate_selection(const std::valarray<real_type>& proportions, const size_type selectedNumber) const -> indices_type {
        real_type overall = proportions.sum();
        std::uniform_real_distribution<real_type> dist (0, overall);
        std::valarray<real_type> roulette = utility::valarray::cumulative_sum(proportions);

        size_type selectedIndex = 0;
        indices_type selected ( selectedNumber );

        for (size_type k = 0; k < selectedNumber; ++k) {
            real_type roll = dist(engine);
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
            real_type diffFitness = fitness[optimaIndex] - min_fitness;
            for (size_type k = 0; k < population_size; ++k)
                relativeFitness[k] = (fitness[k] - min_fitness) / diffFitness;

            size_type medianIndex = algorithm::quick_select<real_type>()(relativeFitness, population_size / 2);

            using ::fn::math::ln;
            real_type base = ::fn::math::square<real_type>()(real_type(1.0) + relativeFitness[medianIndex]);
            std::valarray<real_type> logRelativeFitness = std::log(real_type(1.0) + relativeFitness) / ln<real_type>()(base);
            relativeFitnesses.push_back(std::move(logRelativeFitness));
        }
        std::valarray<real_type> scaledFitness (population_size);
        size_type skipOptimaNumber = 0;
        for (size_type k = 0; k < population_size; ++k) {
            if (skipOptimaNumber < localOptimas.size() && localOptimas[skipOptimaNumber] == k) {
                scaledFitness[k] = 1.0;
                ++skipOptimaNumber;
            }
            else {
                real_type sum = 0, wSum = 0;
                for (size_type optimaNumber = 0; optimaNumber< localOptimas.size(); ++optimaNumber) {
                    size_type optimaIndex = localOptimas[optimaNumber];
                    sum += proximities(optimaIndex, k);
                    wSum += proximities(optimaIndex, k) * relativeFitnesses[optimaNumber][k];
                }
                scaledFitness[k] = wSum / sum;
            }
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
        std::valarray<real_type> inverseDistancesVector = proximities.vector(index, false);
        size_type rankIndex = algorithm::quick_select<real_type>()(inverseDistancesVector, rank);
        real_type rankValue = inverseDistancesVector[rankIndex];
        size_type nearestIndex = 0;
        indices_type nearest (params.nearest_individuals_number);
        for (size_type k = 0; k < population_size; ++k)
            if (inverseDistancesVector[k] > rankValue)
                nearest[nearestIndex++] = k;
        assert(nearest.size() == nearestIndex);
        return nearest;
    }
};

decltype(cmn_ga::default_proximity) cmn_ga::default_proximity = [] (cmn_ga::point_type x, cmn_ga::point_type y)
        -> double {
    return 1.0 / ::utility::math::euclidean_distance<cmn_ga::real_type>()(x, y);
};

}   //-- namespace cmn_ga --
}   //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_CMN_GA_CMN_GA_HPP_ */
