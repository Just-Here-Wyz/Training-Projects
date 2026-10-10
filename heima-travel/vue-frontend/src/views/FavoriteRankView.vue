<template>
  <div>
    <HeaderComp />
    <div class="contant">
      <div class="shaixuan">
        <span>线路名称</span>
        <input type="text" v-model="searchName">
        <span>金额</span>
        <input type="text" v-model="priceMin">~<input type="text" v-model="priceMax">
        <button @click="doSearch">搜索</button>
      </div>
      <div class="list clearfix">
        <ul>
          <li v-for="(item, idx) in rankList" :key="idx">
            <span class="num" :class="{ one: idx === 0, two: idx === 1 }">{{ idx + 1 }}</span>
            <router-link to="/route-detail"><img src="/images/jiangxuan_4.jpg" alt=""></router-link>
            <h4><router-link to="/route-detail">{{ item.name }}</router-link></h4>
            <p>
              <b class="price">&yen;<span>{{ item.price }}</span>起</b>
              <span class="shouchang">已收藏{{ item.count }}次</span>
            </p>
          </li>
        </ul>
      </div>
      <div class="pageNum">
        <ul>
          <li><a href="javascript:;">首页</a></li>
          <li class="threeword"><a href="javascript:;">上一页</a></li>
          <li class="curPage"><a href="javascript:;">1</a></li>
          <li><a href="javascript:;">2</a></li>
          <li><a href="javascript:;">3</a></li>
          <li class="threeword"><a href="javascript:;">下一页</a></li>
          <li class="threeword"><a href="javascript:;">末页</a></li>
        </ul>
      </div>
    </div>
    <FooterComp />
  </div>
</template>

<script setup>
import { ref } from 'vue'
import HeaderComp from '@/components/HeaderComp.vue'
import FooterComp from '@/components/FooterComp.vue'

const searchName = ref('')
const priceMin = ref('')
const priceMax = ref('')

const rankList = ref(Array(8).fill({
  name: '【尾单特卖】全国-曼谷6-7天自由行 泰国出境旅游 特价往6-7天自由行 泰国出境旅游 特价往..',
  price: 899,
  count: 450
}))

function doSearch() {
  // 模拟搜索
}
</script>
