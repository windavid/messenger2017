#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "contact.h"
#include "error.h"
#include "http_connection.h"
#include "abstract_manager.h"

namespace m2 {
namespace core {

    // *********** oved to client/shared_client/contact.h
    //    class ContactBuilder {
    //    public:
    //        std::string uuid;
    //        std::string nickname;
    //        std::string avatar;
    //    };

    //    class Contact {
    //    public:
    //        Contact() {}
    //        Contact(const ContactBuilder &cb)
    //            : uuid_(cb.uuid), nickname_(cb.nickname), avatar_(cb.avatar) {}

    //        std::string GetId() const { return uuid_; }
    //        std::string GetNickname() const { return nickname_; }
    //        std::string GetAvatar() const { return avatar_; }

    //        friend std::istream &operator>>(std::istream &stream, Contact &contact);
    //        friend std::ostream &operator<<(std::ostream &stream, const Contact &contact);

    //    private:
    //        std::string uuid_;
    //        std::string nickname_;
    //        std::string avatar_;
    //    };

    class ContactManager : AbstractManager {
    public:
        using ContactList = std::vector<Contact>;

        void LoadContactList(HttpConnectionPtr connection);
        const ContactList &GetContactList() const;
        void AddContact(const std::string &uuid, const std::string &nickname);

    private:
        void SaveContactList();
        void LoadOffline();
        void LoadOnline(HttpConnectionPtr connection);
        ContactList contactList_;

		Error CheckServerResponse();
		Error CreateContactListFromPtree();
    };

}  // core
}  // m2
