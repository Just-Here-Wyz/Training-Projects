import request from './request'

/**
 * 用户注册
 * 后端接口: POST /regist  (Content-Type: application/x-www-form-urlencoded)
 * @param {Object} formData - 注册表单数据 { username, password, email, name, telephone, sex, birthday, check }
 */
export function registerApi(formData) {
  const params = new URLSearchParams()
  Object.keys(formData).forEach(key => {
    if (formData[key] !== undefined && formData[key] !== null) {
      params.append(key, formData[key])
    }
  })
  return request.post('/regist', params)
}

/**
 * 用户登录
 * 后端接口: POST /login  (Content-Type: application/x-www-form-urlencoded)
 * @param {Object} formData - 登录表单数据 { username, password, check }
 */
export function loginApi(formData) {
  const params = new URLSearchParams()
  Object.keys(formData).forEach(key => {
    if (formData[key] !== undefined && formData[key] !== null) {
      params.append(key, formData[key])
    }
  })
  return request.post('/login', params)
}

/**
 * 退出登录
 * 后端接口: GET /logout
 */
export function logoutApi() {
  return request.get('/logout')
}

/**
 * 获取验证码图片
 * 后端接口: GET /checkCode
 * @returns {Promise<{img: string}>} - base64 编码的验证码图片
 */
export function getCheckCodeApi() {
  return request.get('/checkCode')
}
