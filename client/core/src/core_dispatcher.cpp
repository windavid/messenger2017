﻿#include "stdafx.h"

#include "contact.h"
#include "core.h"
#include "core_dispatcher.h"
#include "handlers.h"
#include "jobtype.h"
#include "message.h"

#include <vector>

namespace m2 {
namespace core {

    void CoreDispatcher::stopCore() { core_->Stop(); }
    void CoreDispatcher::Login(LoginHandler handler) {
        JobType job = [handler](Core &core) {
            std::string uuid = core.GetLoginManager()->Login();
            handler.onCompletion(uuid);
        };
        std::cout << "        push job" << std::endl;
        core_->PushJob(job);
    }

    void CoreDispatcher::RegisterUser(RegisterHandler handler) {
        JobType job = [handler](Core &core) {
            int ret = core.GetLoginManager()->RegisterUser();
            if (ret == 0) {
                handler.onCompletion();
            } else {
                ;
                //      handler.onError();
            }
        };
        std::cout << "        push job" << std::endl;
        core_->PushJob(job);
    }

    void CoreDispatcher::GetServerList(ServerSetHandler handler) {
        JobType job = [handler](Core &core) {
            std::list<std::string> servers = core.GetLoginManager()->GetServerList();
            if (servers.empty()) {
                handler.onCompletion(servers);
            } else {
                ;
                handler.onError();
            }
        };
        std::cout << "        push job get server list" << std::endl;
        core_->PushJob(job);
    }

    void CoreDispatcher::GetMessageStory(const std::string &idStr, MessageStoryHandler handler) {
        // some uber-thread stuff (begin)

        // size_t id =
        // FIXME: int instead of size_t! we need string --> size_t conversion
        int id = std::stoi(idStr);

        if (core_->GetMessageManager()->ChatExists(id)) {
            auto story = core_->GetMessageManager()->GetMessageStory(id);
            handler.onCompletion(story);
        } else
            handler.onError();
        // some uber-thread stuff  (end)
    }
}  // core
}  // m2
