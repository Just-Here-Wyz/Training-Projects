package com.itheima.dao;

import com.itheima.domain.User;
import org.apache.ibatis.annotations.Mapper;

/**
 * 用户数据访问层（MyBatis Mapper 接口）
 *
 * 说明：原始实训交付物中只包含 UserMapper.xml，未包含对应的 Java 接口，
 * 本文件依据 UserService 的实际调用与 XML 中已定义的语句补全，用于保证工程结构完整。
 *
 * ⚠️ 已知问题：UserService 中调用的方法名为 findByUsername，
 *    而 UserMapper.xml 中的语句 id 为 findbyTelephone，两者命名不一致。
 *    直接运行会因语句绑定失败而报错，需将两者统一为同一名称后再运行。
 */
@Mapper
public interface UserMapper {

    /**
     * 按手机号判断用户是否已注册
     * 对应 UserMapper.xml 中的 select id="findbyTelephone"
     */
    boolean findbyTelephone(String telephone);

    /**
     * 新增用户（注册）
     * 对应 UserMapper.xml 中的 insert id="save"
     */
    void save(User user);
}
