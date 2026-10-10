<template>
  <div>
    <HeaderComp />
    <section id="login_wrap">
      <div class="fullscreen-bg" style="background: url(/images/login_bg.png); height: 532px;"></div>
      <div class="login-box">
        <div class="title">
          <img src="/images/login_logo.png" alt="">
          <span>欢迎登录黑马旅游账户</span>
        </div>
        <div class="login_inner">
          <div class="alert alert-danger" v-show="errorMsg">{{ errorMsg }}</div>
          <form @submit.prevent="handleLogin">
            <input v-model="form.username" type="text" placeholder="请输入账号" autocomplete="off">
            <input v-model="form.password" type="password" placeholder="请输入密码" autocomplete="off">
            <div class="verify">
              <input v-model="form.check" type="text" placeholder="请输入验证码" autocomplete="off">
              <span><img :src="checkCodeImg" alt="验证码" @click="refreshCode" style="cursor:pointer;height:32px;" title="点击刷新验证码"></span>
            </div>
            <div class="submit_btn">
              <button type="submit" :disabled="loading">登录</button>
              <div class="auto_login">
                <input type="checkbox" class="checkbox" v-model="form.autoLogin">
                <span>自动登录</span>
              </div>
            </div>
          </form>
          <div class="reg">没有账户？<router-link to="/register">立即注册</router-link></div>
        </div>
      </div>
    </section>
    <FooterComp />
  </div>
</template>

<script setup>
import { ref, reactive, onMounted } from 'vue'
import { useRouter } from 'vue-router'
import HeaderComp from '@/components/HeaderComp.vue'
import FooterComp from '@/components/FooterComp.vue'
import { loginApi, getCheckCodeApi } from '@/api/user'
import { useUserStore } from '@/stores/user'

const router = useRouter()
const userStore = useUserStore()
const errorMsg = ref('')
const loading = ref(false)
const checkCodeImg = ref('')

const form = reactive({
  username: '',
  password: '',
  check: '',
  autoLogin: false
})

// 页面加载时获取验证码
onMounted(() => {
  refreshCode()
})

// 从后端获取验证码图片
async function refreshCode() {
  try {
    const res = await getCheckCodeApi()
    checkCodeImg.value = res.img
  } catch (e) {
    console.error('获取验证码失败', e)
  }
}

// 提交登录表单到后端
async function handleLogin() {
  errorMsg.value = ''
  if (!form.username || !form.password) {
    errorMsg.value = '请输入用户名和密码'
    return
  }
  if (!form.check) {
    errorMsg.value = '请输入验证码'
    return
  }

  loading.value = true
  try {
    const res = await loginApi({
      username: form.username,
      password: form.password,
      check: form.check
    })
    if (res.flag) {
      // 登录成功，保存用户信息到 Pinia store
      userStore.setUser(res.data)
      // 跳转到首页
      router.push('/')
    } else {
      // 登录失败，显示错误信息，刷新验证码
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
