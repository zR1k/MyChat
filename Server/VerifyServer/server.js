'use strict';
const grpc = require('@grpc/grpc-js')
const message_proto = require('./proto')
const const_module = require('./const')
const { v4: uuidv4 } = require('uuid')
const emailMoudle = require('./email')
const redisMoudle = require('./redis')

async function GetVerifyCode(call, callback) {
    console.log('email is ' + call.request.email)

    try {
        let query_res = await redisMoudle.GetRedis(const_module.code_prefix + call.request.email)
        console.log('query res is ' + query_res)
        let uniqueId = query_res
        if (query_res == null) {
            uniqueId = uuidv4();
            if (uniqueId.length > 6) {
                uniqueId = uniqueId.slice(0, 6);
            }
            console.log('uniqueId is ' + uniqueId)
            let set_res = await redisMoudle.SetRedis(const_module.code_prefix + call.request.email, uniqueId, 180);
            console.log('set res is ' + set_res);
            if (set_res == null) {
                callback(null, { 
                    email: call.request.email,
                    error: const_module.Errors.RedisErr,
                });
                return;
            }
        }
        console.log('uniqueId is ' + uniqueId)
        let text_str = '您的验证码是：' + uniqueId + '，请在3分钟内输入。'
        let mailOptions = {
            from: 'songzhenci@126.com',
            to: call.request.email,
            subject: '验证码',
            text: text_str,
        };
        let email_res = await emailMoudle.SendMail(mailOptions)
        console.log('email res is ' + email_res)
        if (email_res == null) {
            callback(null, { 
                email: call.request.email,
                error: const_module.Errors.Exception,
            });
            return
        }

        callback(null, { 
            email: call.request.email,
            error: const_module.Errors.Success,
        });

    } catch (error) {
        console.log('error is ' + error)
        callback(null, { 
            code: const_module.Errors.Exception, 
            error: const_module.Errors.Exception,
        });
    }
}

function main() {
    var server = new grpc.Server()
    server.addService(message_proto.VerifyService.service, { GetVerifyCode: GetVerifyCode })
    server.bindAsync('127.0.0.1:50051', grpc.ServerCredentials.createInsecure(), (err, port) => {
        if (err) {
            console.error('绑定失败:', err);
            return;
        }
        server.start();
        console.log(`grpc 服务器已启动，监听端口 ${port}`);
    })
}

main()