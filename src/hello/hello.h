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

#include "mongo/util/background.h"

namespace mongo {

    class HelloAgent : public BackgroundJob {
    public:

        HelloAgent();

        ~HelloAgent();

        virtual std::string name() const;

        static void init();

        void shutdown();

        void run();

    private:
        void _init();

        int _helloIterations;

    };

}
