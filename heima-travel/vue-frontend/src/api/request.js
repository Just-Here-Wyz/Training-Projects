import axios from 'axios'

// 创建 axios 实例
const request = axios.create({
  // 使用 Vite 代理前缀 /api，会被代理到 http://localhost:8083 并去掉 /api 前缀
  baseURL: '/api',
  timeout: 10000,
  // 携带 Cookie（跨域 session 必须）
  withCredentials: true
})

// 响应拦截器 - 统一处理后端返回格式 { flag, data, errorMsg }
request.interceptors.response.use(
  response => response.data,
  error => {
    console.error('请求失败:', error)
    return Promise.reject(error)
  }
)

export default request
