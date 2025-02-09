const nodeMailer = require('nodemailer');
const config_module = require("./config")

let transporter = nodeMailer.createTransport({
    host: 'smtp.126.com',
    port: 465,
    secure: true,
    auth: {
        user: config_module.email_user,
        pass: config_module.email_pass
    }
});

function sendEmail(mailoptions) {
    return new Promise(function(resolve, reject) {
        transporter.sendMail(mailoptions, function(error, info) {
            if (error) {
                console.log(error);
                reject(error);
            } else {
                console.log('邮件发送成功: ' + info.response);
                resolve(info.response);
            }
        });
    })
}

module.exports.SendMail = sendEmail;