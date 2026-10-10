<template>
  <div>
    <HeaderComp />
    <div class="rg_layout">
      <div class="rg_form clearfix">
        <div class="rg_form_left">
          <p>新用户注册</p>
          <p>USER REGISTER</p>
        </div>
        <div class="rg_form_center">
          <div id="errorMsg" style="color:red;text-align:center" v-show="errorMsg">{{ errorMsg }}</div>
          <form @submit.prevent="handleRegister">
            <table style="margin-top:25px;">
              <tr>
                <td class="td_left"><label for="username">用户名</label></td>
                <td class="td_right"><input type="text" id="username" v-model="form.username" placeholder="请输入账号" :class="{ 'input-error': errors.username }" @blur="checkUsername"></td>
              </tr>
              <tr>
                <td class="td_left"><label for="password">密码</label></td>
                <td class="td_right"><input type="password" id="password" v-model="form.password" placeholder="请输入密码" :class="{ 'input-error': errors.password }" @blur="checkPassword"></td>
              </tr>
              <tr>
                <td class="td_left"><label for="email">Email</label></td>
                <td class="td_right"><input type="text" id="email" v-model="form.email" placeholder="请输入Email" :class="{ 'input-error': errors.email }" @blur="checkEmail"></td>
              </tr>
              <tr>
                <td class="td_left"><label for="name">姓名</label></td>
                <td class="td_right"><input type="text" id="name" v-model="form.name" placeholder="请输入真实姓名"></td>
              </tr>
              <tr>
                <td class="td_left"><label for="telephone">手机号</label></td>
                <td class="td_right"><input type="text" id="telephone" v-model="form.telephone" placeholder="请输入您的手机号"></td>
              </tr>
              <tr>
                <td class="td_left"><label for="sex">性别</label></td>
                <td class="td_right gender">
                  <input type="radio" v-model="form.sex" value="男" checked> 男
                  <input type="radio" v-model="form.sex" value="女"> 女
                </td>
              </tr>
              <tr>
                <td class="td_left"><label for="birthday">出生日期</label></td>
                <td class="td_right"><input type="date" id="birthday" v-model="form.birthday" placeholder="年/月/日"></td>
              </tr>
              <tr>
                <td class="td_left"><label for="check">验证码</label></td>
                <td class="td_right check">
                  <input type="text" id="check" v-model="form.check" class="check">
                  <img :src="checkCodeImg" height="32px" alt="验证码" @click="refreshCode" style="cursor:pointer;" title="点击刷新验证码">
                </td>
              </tr>
              <tr>
                <td class="td_left"></td>
                <td class="td_right check">
                  <input type="submit" class="submit" value="注册" :disabled="loading">
                </td>
              </tr>
            </table>
          </form>
        </div>
        <div class="rg_form_right">
          <p>已有账号？<router-link to="/login">立即登录</router-link></p>
        </div>
      </div>
    </div>
    <FooterComp />
  </div>
</template>

<script setup>
import { ref, reactive, onMounted } from 'vue'
import { useRouter } from 'vue-router'
import HeaderComp from '@/components/HeaderComp.vue'
import FooterComp from '@/components/FooterComp.vue'
import { registerApi, getCheckCodeApi } from '@/api/user'

const router = useRouter()
const errorMsg = ref('')
const loading = ref(false)
const checkCodeImg = ref('')
const errors = reactive({ username: false, password: false, email: false })

const form = reactive({
  username: '', password: '', email: '', name: '',
  telephone: '', sex: '男', birthday: '', check: ''
})

// 页面加载时获取验证码
onMounted(() => {
  refreshCode()
})

function checkUsername() {
  errors.username = !/^\w{8,20}$/.test(form.username)
  return !errors.username
}
function checkPassword() {
  errors.password = !/^\w{8,20}$/.test(form.password)
  return !errors.password
}
function checkEmail() {
  errors.email = !/^\w+@\w+\.\w+$/.test(form.email)
  return !errors.email
}

// 从后端获取验证码图片
async function refreshCode() {
  try {
    const res = await getCheckCodeApi()
    checkCodeImg.value = res.img
  } catch (e) {
    console.error('获取验证码失败', e)
  }
}

// 提交注册表单到后端
async function handleRegister() {
  errorMsg.value = ''
  if (!checkUsername() || !checkPassword() || !checkEmail()) {
    errorMsg.value = '请检查用户名、密码和邮箱格式'
    return
  }
  if (!form.telephone) {
    errorMsg.value = '请输入手机号'
    return
  }
  if (!form.check) {
    errorMsg.value = '请输入验证码'
    return
  }

  loading.value = true
  try {
    const res = await registerApi(form)
    if (res.flag) {
      // 注册成功，跳转到成功页面
      router.push('/register-ok')
    } else {
      // 注册失败，显示后端错误信息，并刷新验证码
      errorMsg.value = res.errorMsg
      refreshCode()
    }
  } catch (e) {
    errorMsg.value = '网络错误，请稍后重试'
    refreshCode()
  } finally {
    loading.value = false
  }
}
</script>

<style scoped>
.input-error { border: 1px solid red !important; }
</style>
