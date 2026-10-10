<template>
  <div>
    <HeaderComp />
    <section id="content">
      <section class="hemai_jx">
        <div class="jx_top">
          <div class="jx_tit">
            <img src="/images/icon_5.jpg" alt="">
            <span>我的收藏</span>
          </div>
        </div>
        <div class="jx_content">
          <div class="tab-content">
            <div class="tab-pane active">
              <div class="row">
                <div class="col-md-3" v-for="(item, idx) in favorites" :key="idx">
                  <router-link to="/route-detail">
                    <img src="/images/collection_pic.jpg" alt="">
                    <div class="has_border">
                      <h3>{{ item.title }}</h3>
                      <div class="price">网付价<em>￥</em><strong>{{ item.price }}</strong><em>起</em></div>
                    </div>
                  </router-link>
                </div>
              </div>
            </div>
          </div>
        </div>
        <div class="pageNum">
          <ul>
            <li><a href="javascript:;">首页</a></li>
            <li class="threeword"><a href="javascript:;">上一页</a></li>
            <li class="curPage"><a href="javascript:;">1</a></li>
            <li><a href="javascript:;">2</a></li>
            <li class="threeword"><a href="javascript:;">下一页</a></li>
            <li class="threeword"><a href="javascript:;">末页</a></li>
          </ul>
        </div>
      </section>
    </section>
    <FooterComp />
  </div>
</template>

<script setup>
import { ref } from 'vue'
import HeaderComp from '@/components/HeaderComp.vue'
import FooterComp from '@/components/FooterComp.vue'

const favorites = ref(Array(12).fill({
  title: '上海直飞三亚5天4晚自由行(春节预售+亲子/蜜月/休闲游首选+豪华酒店任选+接送机)',
  price: 889
}))
</script>

<style scoped>
.tab-content .row > div { margin-top: 16px; }
.tab-content { margin-bottom: 36px; }
</style>
