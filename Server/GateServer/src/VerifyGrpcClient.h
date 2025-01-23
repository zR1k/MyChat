#pragma once 

#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVerifyReq;
using message::GetVerifyResp;
using message::VerifyService;

class VerifyGrpcClient : public Singleton<VerifyGrpcClient> {
    friend class Singleton<VerifyGrpcClient>;
public:
    GetVerifyResp GetVerifyCode(std::string email) {
        ClientContext context;
        GetVerifyReq req;
        GetVerifyResp resp;

        req.set_email(email);
        Status status = stub_->GetVerifyCode(&context, req, &resp);
        if(!status.ok()) {
            // std::cout << "GetVerifyCode rpc failed" << std::endl;
            resp.set_error(ErrorCodes::RPCFalied);
        }
        return resp;
    }

private:
    std::unique_ptr<VerifyService::Stub> stub_;
    VerifyGrpcClient() {
        std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:50051", 
            grpc::InsecureChannelCredentials());
        stub_ = VerifyService::NewStub(channel);
    }
};