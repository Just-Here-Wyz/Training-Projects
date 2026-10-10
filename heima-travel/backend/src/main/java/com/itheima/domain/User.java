package com.itheima.domain;

import lombok.Data;

// 注册的数据传输对象
@Data
public class User {

    private int uid;
    private String username;  // 用户名
    private String password; // 密码
    private String name;    // 真实姓名
    private String birthday; // 生日
    private String sex;   //   性别
    private String telephone; // 电话
    private String email;   //  邮箱
    private String status; // 状态
    private String code;  // 验证码
    private String nickname; // 昵称
    private String registTime; // 注册时间
    private String updateTime; // 更新时间

}
