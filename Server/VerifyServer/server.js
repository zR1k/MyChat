const grpc = require('@grpc/grpc-js')
const message_proto = require('./proto')
const const_module = require('./const')
const { v4: uuidv4 } = require('uuid')
const emailMoudle = require('./email')

async function GetVerifyCode(call, callback) {
    console.log('email is ' + call.request.email)

    try{
        uniqueId = uuidv4()
        console.log('uniqueId is ' + uniqueId)
        let text_str = '您的验证码是：' + uniqueId + '，请在三分组内完成注册。'

        let mailOptions = {
            from: 'songzhenci@126.com',
            to: call.request.email,
            subject: '验证码',
            text: text_str
        };

        let send_res = await emailMoudle.SendMail(mailOptions)
        console.log('send res is ' + send_res)
        
        callback (null, { email: call.request.email, 
                error: const_module.Errors.Success,
                code: uniqueId });
        
    } catch (error) {
        console.log('error is ' + error)
        callback (null, { email: call.request.email, 
            error: const_module.Errors.Exception,
         code: ''    });
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