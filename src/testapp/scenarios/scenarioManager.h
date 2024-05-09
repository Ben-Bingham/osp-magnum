/**
 * Open Space Program
 * Copyright � 2019-2021 Open Space Program Project
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "../scenario.h"

namespace testapp
{

/*
* @brief Singleton class that stores get_scenarios, and allows retrieval of get_scenarios by name.
*/
class ScenarioManager
{
public:
	~ScenarioManager() = default;
	ScenarioManager(ScenarioManager const&) = delete;
	void operator=(ScenarioManager const&) = delete;
	ScenarioManager(ScenarioManager&& other) noexcept = delete;
	ScenarioManager& operator=(ScenarioManager&& other) noexcept = delete;

	/*
	 * @brief Returns the instance of the Singleton.
	*/
	static ScenarioManager& get();

	bool has_scenario(const std::string& scenarioName);

	/*
	 * @brief Returns the scenario of the given name, call has_scenario first.
	 *
	 * Only call this function if you receive a true return value from has_scenario.
	 * otherwise this function returns an invalid scenario.
	*/
	Scenario get_scenario(const std::string& scenarioName);

	/*
	 * @brief Only adds the scenario if a scenario with that name is not already stored.
	*/
	void add_scenario(const Scenario& scenario);

	std::vector<Scenario> get_scenarios() const;

private:
    ScenarioManager();

	std::vector<Scenario> m_scenarios;
};

}