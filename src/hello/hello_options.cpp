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

#include "mongo/platform/basic.h"

#include "hello_options.h"

#include <string>
#include <vector>

#include "mongo/base/status.h"
#include "mongo/db/server_options.h"
#include "mongo/util/options_parser/option_description.h"
#include "mongo/util/options_parser/option_section.h"
#include "mongo/util/options_parser/options_parser.h"
#include "mongo/util/options_parser/startup_option_init.h"
#include "mongo/util/options_parser/startup_options.h"

namespace mongo {

    HelloParams helloParams;

    Status addHelloOptions(moe::OptionSection* options) {

        moe::OptionSection hello_options("Hello Module Options");

        hello_options.addOptionChaining("hello.agent", "run-hello", moe::Switch,
                                       "Run hello agent");
        hello_options.addOptionChaining("hello.greeting", "hello-greeting", moe::String,
                                        "Custom greeting. Implies --run-hello")
                                        .setDefault(moe::Value(std::string("Bonjour")));

        Status ret = options->addSection(hello_options);
        if (!ret.isOK()) {
            return ret;
        }

        return Status::OK();
    }

    Status storeHelloOptions(const moe::Environment& params,
                             const std::vector<std::string>& args) {

        if (params.count("hello.agent")) {
            helloParams.enabled = true;
        }
        if (params.count("hello.greeting")) {
            helloParams.enabled = true;
            helloParams.greeting = params["hello.greeting"].as<string>();
        }

        return Status::OK();
    }

    MONGO_MODULE_STARTUP_OPTIONS_REGISTER(HelloOptions)(InitializerContext* context) {
        return addHelloOptions(&moe::startupOptions);
    }

    MONGO_STARTUP_OPTIONS_STORE(HelloOptions)(InitializerContext* context) {
        return storeHelloOptions(moe::startupOptionsParsed, context->args());
    }

} // namespace mongo
