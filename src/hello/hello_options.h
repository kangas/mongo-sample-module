/*    Copyright 2014 MongoDB Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <string>
#include <vector>

#include "mongo/base/status.h"

namespace mongo {

    namespace optionenvironment {
        class Environment;
        class OptionSection;
    } // namespace optionenvironment

    namespace moe = mongo::optionenvironment;

    struct HelloParams {

        HelloParams() : enabled(false) {}

        bool enabled;
        std::string greeting;
    };

    extern HelloParams helloParams;

    Status addHelloOptions(moe::OptionSection* options);

    Status storeHelloOptions(const moe::Environment& params,
                             const std::vector<std::string>& args);
}
