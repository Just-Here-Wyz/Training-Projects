<template>
  <div>
    <HeaderComp />
    <div style="text-align:center;padding:100px 0;font-size:24px;color:#666;">
      <h1 style="font-size:72px;color:#ffc900;">404</h1>
      <p>抱歉，您访问的页面不存在</p>
      <router-link to="/" style="color:#ffc900;font-size:16px;">返回首页</router-link>
    </div>
    <FooterComp />
  </div>
</template>

<script setup>
import HeaderComp from '@/components/HeaderComp.vue'
import FooterComp from '@/components/FooterComp.vue'
</script>
