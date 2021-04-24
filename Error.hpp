//
//  Error.hpp
//  PA7
//
//  Created by Kyle Parker on 3/31/21.
//

#ifndef Error_hpp
#define Error_hpp

class Error final {
    std::string internalDescription;
    UInt internalErrorCode;
    std::map<std::string, std::string> internalUserInfo;
    
public:
    Error(void) {
        this->internalDescription = "Unknown";
        this->internalErrorCode = 0x00000000;
        this->internalUserInfo = {{"description","Unknown"}};
    }
    
    Error(const UInt errorCode) {
        this->internalErrorCode = errorCode;
        this->internalUserInfo = {};
    }
    
    Error(const std::map<std::string,std::string> userInfo) {
        this->internalDescription = "Unknown Error Occured.";
        this->internalErrorCode = 0x00000000;
        this->internalUserInfo = userInfo;
    }
    
    Error(const std::string description, const UInt errorCode, std::map<std::string, std::string> userInfo = {}) {
        this->internalDescription = description;
        this->internalErrorCode = errorCode;
        
        if (userInfo == std::map<std::string,std::string>()) { //check for empty
            userInfo = {{"description",description}};
        }
        
        this->internalUserInfo = userInfo;
    }
    
    Error(const std::string description, const std::map<std::string, std::string> userInfo = {}) {
        this->internalDescription = description;
        this->internalErrorCode = 0x00000000;
        this->internalUserInfo = userInfo;
    }
    
    void updateDescription(const std::string str) {
        this->internalDescription = str;
        
        std::map<std::string, std::string>::iterator target = internalUserInfo.find("description");
        if (target != internalUserInfo.end()) {
            target->second = str;
        } else {
            internalUserInfo.insert(make_pair("description",str));
        }
    }
    
    std::string description() { return this->internalDescription; }
    UInt code() { return this->internalErrorCode; }
    std::map<std::string, std::string> userInfo() { return this->internalUserInfo; }
};

std::ostream & operator <<(std::ostream & lhs, Error & rhs) {
    return lhs << "Description: " << rhs.description() << "\nCode: " << rhs.code() << "\nUserInfo: ";// << rhs.userInfo();
}

#endif /* Error_hpp */
