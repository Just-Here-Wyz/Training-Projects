<template>
  <div>
    <HeaderComp />
    <div class="page_one">
      <div class="contant">
        <div class="crumbs">
          <img src="/images/search.png" alt="">
          <p>黑马旅行><span>搜索结果</span></p>
        </div>
        <div class="xinxi clearfix">
          <div class="left">
            <div class="header">
              <span>商品信息</span>
              <span class="jg">价格</span>
            </div>
            <ul id="route">
              <li v-for="(item, idx) in routeList" :key="idx">
                <div class="img"><img :src="item.rimage" style="width:299px;"></div>
                <div class="text1">
                  <p>{{ item.rname }}</p><br/>
                  <p>{{ item.routeIntroduce }}</p>
                </div>
                <div class="price">
                  <p class="price_num">
                    <span>&yen;</span>
                    <span>{{ item.price }}</span>
                    <span>起</span>
                  </p>
                  <p><router-link :to="'/route-detail?rid=' + item.rid">查看详情</router-link></p>
                </div>
              </li>
            </ul>
            <div class="page_num_inf">
              <i></i> 共<span>{{ totalPage }}</span>页<span>{{ totalCount }}</span>条
            </div>
            <div class="pageNum">
              <ul>
                <li @click="load(1)"><a href="javascript:;">首页</a></li>
                <li class="threeword" @click="load(currentPage - 1)"><a href="javascript:;">上一页</a></li>
                <li v-for="p in displayPages" :key="p" :class="{ curPage: currentPage === p }" @click="load(p)">
                  <a href="javascript:;">{{ p }}</a>
                </li>
                <li class="threeword" @click="load(currentPage + 1)"><a href="javascript:;">下一页</a></li>
                <li class="threeword" @click="load(totalPage)"><a href="javascript:;">末页</a></li>
              </ul>
            </div>
          </div>
          <div class="right">
            <div class="top">
              <div class="hot">HOT</div>
              <span>热门推荐</span>
            </div>
            <ul>
              <li v-for="(item, idx) in hotItems" :key="idx">
                <div class="left"><img src="/images/04-search_09.jpg" alt=""></div>
                <div class="right">
                  <p>{{ item.name }}</p>
                  <p>网付价<span>&yen;<span>{{ item.price }}</span>起</span></p>
                </div>
              </li>
            </ul>
          </div>
        </div>
      </div>
    </div>
    <FooterComp />
  </div>
</template>

<script setup>
import { ref, computed, onMounted, watch } from 'vue'
import { useRoute } from 'vue-router'
import HeaderComp from '@/components/HeaderComp.vue'
import FooterComp from '@/components/FooterComp.vue'

const route = useRoute()
const currentPage = ref(1)
const totalPage = ref(12)
const totalCount = ref(132)

const routeList = ref([
  { rid: 1, rname: '【减100元 含除夕/春节出发】广州增城三英温泉度假酒店/自由行套票', routeIntroduce: '1-2月出发，网付立享￥1099/2人起！爆款位置有限，抢完即止！', price: 299, rimage: '/images/04-search_03.jpg' },
  { rid: 2, rname: '浪花朵朵旅行普吉岛丛林飞跃空中飞人探险游中文服务泰国旅游', routeIntroduce: '1-2月出发，网付立享￥1099/2人起！', price: 899, rimage: '/images/04-search_03.jpg' },
  { rid: 3, rname: '黑妞皇家旅行普吉岛攀牙湾大船星光之旅皮划艇日落休闲特色体验', routeIntroduce: '1-2月出发，网付立享￥1099/2人起！', price: 999, rimage: '/images/04-search_03.jpg' },
  { rid: 4, rname: '浪花朵朵旅行普吉岛皇帝岛珊瑚岛香蕉船拖拽伞水上项目', routeIntroduce: '1-2月出发，网付立享￥1099/2人起！', price: 99, rimage: '/images/04-search_03.jpg' },
  { rid: 5, rname: '环游记 泰国清迈Lila massage女子监狱spa 丽菈泰式按摩马杀鸡', routeIntroduce: '1-2月出发，网付立享￥1099/2人起！', price: 199, rimage: '/images/04-search_03.jpg' },
  { rid: 6, rname: '泰国芭提雅三合一日游芭提雅蒂芬妮人妖秀成人门票bigeye含接送', routeIntroduce: '1-2月出发，网付立享￥1099/2人起！', price: 1589, rimage: '/images/04-search_03.jpg' },
])

const hotItems = ref(Array(5).fill({ name: '清远新银盏温泉度假村酒店/自由行套...', price: 899 }))

const displayPages = computed(() => {
  let begin = currentPage.value - 5
  let end = currentPage.value + 4
  if (begin < 1) { begin = 1; end = Math.min(10, totalPage.value) }
  if (end > totalPage.value) { end = totalPage.value; begin = Math.max(1, end - 9) }
  const pages = []
  for (let i = begin; i <= end; i++) pages.push(i)
  return pages
})

function load(page) {
  if (page < 1) page = 1
  if (page > totalPage.value) page = totalPage.value
  currentPage.value = page
}

onMounted(() => { load(1) })
</script>
