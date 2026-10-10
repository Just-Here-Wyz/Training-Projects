package com.itheima.service;

import com.itheima.dao.UserMapper;
import com.itheima.domain.User;
import com.itheima.util.MailUtils;
import com.itheima.util.UuidUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
// SERVICE
@Service
//用户服务
public class UserService {


    // 引入下一层的Mapper
    @Autowired
    private  UserMapper  userMapper;

    //注册用户
    public Boolean regist(User user) {

        // 注册的时候  程序判断 你是否注册过   数据库当中有没有相同的用户名
        User user1 = userMapper.findByUsername(user.getTelephone());
         // 曾经注册过 所以不用等空
           if (user1 !=null){
               return false;
           }
           // 保存点新的数据   更新数据
           user.setCode(UuidUtil.getUuid());
           user.setStatus("N");
           // 数据库的保存功能  保存到数据库
            userMapper.save(user);
        // 发邮件
        MailUtils mailUtils = new MailUtils();
        // 邮箱   code  注册嘛      标题
        mailUtils.sendMail(user.getEmail(), "你好我是邮箱 欢迎您注册", "激活邮件");
           // 没有注册过  保存到数据库当中 注册       // 下一层了
        return  true;;
    }

}
