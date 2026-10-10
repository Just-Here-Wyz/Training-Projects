import { defineStore } from 'pinia'
import { ref, computed } from 'vue'

export const useUserStore = defineStore('user', () => {
  // 从 localStorage 恢复用户状态（刷新页面后保持登录态）
  const savedUser = JSON.parse(localStorage.getItem('user') || 'null')
  const user = ref(savedUser)

  // 是否已登录
  const isLoggedIn = computed(() => !!user.value)

  // 设置用户信息（登录成功时调用）
  function setUser(userData) {
    user.value = userData
    localStorage.setItem('user', JSON.stringify(userData))
  }

  // 清除用户信息（退出登录时调用）
  function clearUser() {
    user.value = null
    localStorage.removeItem('user')
  }

  return { user, isLoggedIn, setUser, clearUser }
})
