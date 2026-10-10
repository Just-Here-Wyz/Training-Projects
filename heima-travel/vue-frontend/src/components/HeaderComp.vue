<template>
  <header id="header">
    <div class="top_banner">
      <img src="/images/top_banner.jpg" alt="">
    </div>
    <div class="shortcut">
      <div class="login_out" v-if="!userStore.isLoggedIn">
        <router-link to="/login">登录</router-link>
        <router-link to="/register">注册</router-link>
      </div>
      <div class="login" v-else>
        <span id="span_username">欢迎回来，{{ userStore.user.name || userStore.user.nickname || userStore.user.username }}</span>
        <router-link to="/my-favorite" class="collection">我的收藏</router-link>
        <a href="javascript:;" @click="logout">退出</a>
      </div>
    </div>
    <div class="header_wrap">
      <div class="topbar">
        <div class="logo">
          <router-link to="/"><img src="/images/logo.jpg" alt=""></router-link>
        </div>
        <div class="search">
          <input id="search_input" type="text" placeholder="请输入路线名称" class="search_input" v-model="searchText" @keyup.enter="doSearch" />
          <a href="javascript:;" class="search-button" @click="doSearch">搜索</a>
        </div>
        <div class="hottel">
          <div class="hot_pic">
            <img src="/images/hot_tel.jpg" alt="">
          </div>
          <div class="hot_tel">
            <p class="hot_time">客服热线(9:00-6:00)</p>
            <p class="hot_num">400-618-9090</p>
          </div>
        </div>
      </div>
    </div>
  </header>
  <div class="navitem">
    <ul class="nav">
      <li :class="{ 'nav-active': isActive('/') }">
        <router-link to="/">首页</router-link>
      </li>
      <li v-for="cat in categories" :key="cat.cid" :class="{ 'nav-active': isActive('/route-list?cid=' + cat.cid) }">
        <router-link :to="'/route-list?cid=' + cat.cid">{{ cat.cname }}</router-link>
      </li>
      <li :class="{ 'nav-active': isActive('/favorite-rank') }">
        <router-link to="/favorite-rank">收藏排行榜</router-link>
      </li>
    </ul>
  </div>
</template>

<script setup>
import { ref, reactive } from 'vue'
import { useRouter, useRoute } from 'vue-router'
import { useUserStore } from '@/stores/user'
import { logoutApi } from '@/api/user'

const router = useRouter()
const route = useRoute()
const userStore = useUserStore()
const searchText = ref('')

// 模拟分类数据（后续可对接后端分类接口）
const categories = reactive([
  { cid: 1, cname: '门票' },
  { cid: 2, cname: '酒店' },
  { cid: 3, cname: '香港车票' },
  { cid: 4, cname: '出境游' },
  { cid: 5, cname: '国内游' },
  { cid: 6, cname: '港澳游' },
  { cid: 7, cname: '抱团定制' },
  { cid: 8, cname: '全球自由行' },
])

function isActive(path) {
  return route.fullPath === path
}

function doSearch() {
  if (searchText.value.trim()) {
    router.push({ path: '/route-list', query: { rname: searchText.value } })
  }
}

// 退出登录：调用后端接口清除 session，清除前端状态
async function logout() {
  try {
    await logoutApi()
  } catch (e) {
    // 即使后端请求失败，也要清除前端状态
  }
  userStore.clearUser()
  router.push('/login')
}
</script>
