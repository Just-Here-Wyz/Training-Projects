# 黑马旅游网 / Heima Travel Website

旅游线路展示与用户注册的 Web 全栈项目，包含三个部分：
原始 HTML 静态站、Spring Boot 后端服务，以及改造后的 Vue 3 前端工程。

## 目录结构

```
heima-travel/
├── frontend/       原始 HTML 版本（Bootstrap + jQuery 静态页面）
├── backend/        Spring Boot 后端（用户注册 + 邮件激活）
└── vue-frontend/   Vue 3 + Vite 改造版前端
```

## 一、frontend — 原始 HTML 版本

纯静态页面，直接用浏览器打开 `frontend/index.html` 即可预览。

| 页面 | 说明 |
|---|---|
| `index.html` | 首页，旅游线路推荐 |
| `route_list.html` | 线路列表与搜索 |
| `route_detail.html` | 线路详情 |
| `login.html` / `register.html` / `register_ok.html` | 登录注册流程 |
| `myfavorite.html` / `favoriterank.html` | 我的收藏、收藏排行榜 |
| `header.html` / `footer.html` | 公共头部与底部 |
| `error/404.html`、`error/500.html` | 错误页 |

## 二、backend — Spring Boot 后端

**技术栈**：Spring Boot 3.2 / MyBatis-Plus / Druid 连接池 / MySQL 8 / Lombok

```
backend/
├── pom.xml
├── sql/travel.sql                          数据库脚本
└── src/main/
    ├── java/com/itheima/
    │   ├── domain/User.java                用户实体
    │   ├── service/UserService.java        注册业务（查重、写库、发激活邮件）
    │   ├── dao/UserMapper.java             Mapper 接口
    │   └── util/ResultInfo.java            统一响应封装
    ├── java/cn/itcast/travel/util/
    │   ├── MailUtils.java                  邮件发送
    │   └── UuidUtil.java                   激活码生成
    └── resources/
        ├── application.yml
        └── mapper/UserMapper.xml
```

### 运行步骤

1. MySQL 中导入 `backend/sql/travel.sql`
2. 在 `src/main/resources/application.yml` 中把 `YOUR_DB_PASSWORD` 改为本机 MySQL 密码
3. `cd backend && mvn spring-boot:run`，服务启动在 **8083** 端口

### 说明

`pom.xml` 与 `UserMapper.java` 为整理归档时补全——原始实训交付物中只有散落的
`.java` 源文件与 `UserMapper.xml`，没有构建文件与 Mapper 接口。

### 已知问题

`UserService` 中调用的方法名为 `findByUsername`，而 `UserMapper.xml` 中定义的语句 id
为 `findbyTelephone`，**两者命名不一致**，直接运行会因语句绑定失败而报错。
需将二者统一为同一名称（例如都改成 `findbyTelephone`）后注册功能才能正常工作。

## 三、vue-frontend — Vue 3 改造版

在原 HTML 版本基础上改造的单页应用。

**技术栈**：Vue 3.5 / Vite 6 / Vue Router 4 / Pinia 3 / Axios / Bootstrap

```
vue-frontend/
├── index.html
├── package.json
├── vite.config.js         已配置 /api 代理到后端 8083 端口
└── src/
    ├── views/             11 个页面组件
    ├── components/        HeaderComp、FooterComp
    ├── router/index.js
    ├── stores/user.js     用户状态（Pinia）
    └── api/               Axios 请求封装
```

### 运行步骤

```bash
cd vue-frontend
npm install
npm run dev        # 开发服务器运行在 8080 端口
```

### 说明

为控制仓库体积，本目录**只保留了源码**，未包含 `node_modules`、构建产物 `dist`
以及图片资源。若需完整预览，请将 `frontend/` 下的 `img` 与 `images` 目录
复制到 `vue-frontend/public/` 中。
