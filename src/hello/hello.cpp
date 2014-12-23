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

#define MONGO_LOG_DEFAULT_COMPONENT ::mongo::logger::LogComponent::kControl

#include "mongo/platform/basic.h"

#include "hello.h"

#include <string>

#include "mongo/base/init.h"
#include "mongo/db/db.h"            // see HORRIBLE HACK below
#include "mongo/util/log.h"
#include "mongo/util/options_parser/option_description.h"

#include "hello_options.h"

namespace mongo {

    namespace moe = mongo::optionenvironment;

    HelloAgent helloAgent;

    HelloAgent::HelloAgent() {
    }

    HelloAgent::~HelloAgent() {
    }

    /* virtual */ std::string HelloAgent::name() const {
        return "HelloAgent";
    }

    void HelloAgent::shutdown() {
        helloParams.enabled = 0;
    }

    void HelloAgent::run() {

        if (!helloParams.enabled) {
            LOG(1) << "HelloAgent not enabled";
            return;
        }

        log() << "HelloAgent started" << endl;
        _init();

        while(helloParams.enabled && !inShutdown()) {
            _helloIterations++;
            log() << helloParams.greeting << " " << _helloIterations;
            sleepsecs(1);
        }

        log() << "HelloAgent shutting down" << endl;
    }

    void HelloAgent::_init() {
        Client::initThread("HelloAgent");
    }

    /* static */ void HelloAgent::init() {
        helloAgent.go();
    }

    MONGO_INITIALIZER(InitializeHello)(InitializerContext* context) {
        // HORRIBLE HACK to start thread later
        // Threads cannot be started in initalizers
        snmpInit = &HelloAgent::init;
        return Status::OK();
    }

}
