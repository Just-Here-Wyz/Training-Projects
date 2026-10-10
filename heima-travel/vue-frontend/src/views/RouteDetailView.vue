<template>
  <div>
    <HeaderComp />
    <div class="wrap">
      <div class="bread_box">
        <router-link to="/">首页</router-link>
        <span> &gt;</span>
        <a href="javascript:;">国内游</a><span> &gt;</span>
        <a href="javascript:;">{{ route.name }}</a>
      </div>
      <div class="prosum_box">
        <dl class="prosum_left">
          <dt><img class="big_img" :src="bigPic" alt=""></dt>
          <dd>
            <a class="up_img up_img_disable" @click="scrollUp"></a>
            <a v-for="(img, idx) in visibleThumbs" :key="idx"
               class="little_img" :class="{ 'cur_img': img === bigPic }"
               @mousemove="bigPic = img">
              <img :src="img">
            </a>
            <a class="down_img down_img_disable" @click="scrollDown"></a>
          </dd>
        </dl>
        <div class="prosum_right">
          <p class="pros_title">{{ route.name }}</p>
          <p class="hot">{{ route.introduce }}</p>
          <div class="pros_other">
            <p>经营商家：{{ route.seller }}</p>
            <p>咨询电话：{{ route.phone }}</p>
            <p>地址：{{ route.address }}</p>
          </div>
          <div class="pros_price">
            <p class="price"><strong>¥{{ route.price }}</strong><span>起</span></p>
            <p class="collect">
              <a class="btn" :class="{ already: isFavorite }" @click="addFavorite">
                ♥ {{ isFavorite ? '已收藏' : '点击收藏' }}
              </a>
              <span>已收藏{{ favoriteCount }}次</span>
            </p>
          </div>
        </div>
      </div>
      <div class="you_need_konw">
        <span>旅游须知</span>
        <div class="notice">
          <p>1、旅行社已投保旅行社责任险。建议游客购买旅游意外保险。</p>
          <p>2、旅游者参加高风险性游乐项目前，请务必充分了解安全须知并确保身体状况能适应此类活动。</p>
          <p>3、参加出海活动时，请务必穿着救生设备。老人和小孩必须有成年人陪同才能参加合适的水上活动。</p>
          <p>4、根据中国海关总署的规定，旅客在境外购买的物品在进入中国海关时可能需要征收关税。</p>
          <p>5、建议出发时行李托运，贵重物品、常用物品、常用药品、御寒衣物等请随身携带。</p>
        </div>
      </div>
    </div>
    <FooterComp />
  </div>
</template>

<script setup>
import { ref, reactive, computed } from 'vue'
import HeaderComp from '@/components/HeaderComp.vue'
import FooterComp from '@/components/FooterComp.vue'

const bigPic = ref('/img/product/size4/m29788843d72171643297ccc033d9288ee.jpg')
const thumbPics = [
  '/img/product/size2/m20920d0669855e745d97f9ad1df966ebb.jpg',
  '/img/product/size2/m29788843d72171643297ccc033d9288ee.jpg',
  '/img/product/size2/m2531a8dbceefa2c44e6d0e35627cd2689.jpg',
  '/img/product/size2/m26d8cb900e9f6c0a762aca19eae40c00c.jpg',
]
const bigPics = [
  '/img/product/size4/m40920d0669855e745d97f9ad1df966ebb.jpg',
  '/img/product/size4/m49788843d72171643297ccc033d9288ee.jpg',
  '/img/product/size4/m4531a8dbceefa2c44e6d0e35627cd2689.jpg',
  '/img/product/size4/m46d8cb900e9f6c0a762aca19eae40c00c.jpg',
]

const visibleThumbs = computed(() => bigPics.slice(0, 4))

const route = reactive({
  name: '【尾单特卖】全国-曼谷6-7天自由行 泰国出境旅游 特价往返机票自由行二次确认',
  introduce: '1-2月出发，网付立享￥1099/2人起！爆款位置有限，抢完即止！',
  price: '2699.00',
  seller: '黑马国旅',
  phone: '400-618-9090',
  address: '传智播客黑马程序员'
})

const isFavorite = ref(false)
const favoriteCount = ref(100)

function addFavorite() {
  if (!isFavorite.value) {
    isFavorite.value = true
    favoriteCount.value++
  }
}
function scrollUp() {}
function scrollDown() {}
</script>
