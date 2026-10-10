<template>
  <div>
    <HeaderComp />
    <!-- Banner -->
    <section id="banner">
      <div class="carousel-wrap">
        <div class="carousel-inner">
          <img v-for="(img, idx) in banners" :key="idx" :src="img" :class="{ active: currentBanner === idx }" />
        </div>
        <div class="carousel-indicators">
          <span v-for="(img, idx) in banners" :key="idx" :class="{ active: currentBanner === idx }" @click="currentBanner = idx"></span>
        </div>
        <a class="carousel-control left" @click="prevBanner">&lsaquo;</a>
        <a class="carousel-control right" @click="nextBanner">&rsaquo;</a>
      </div>
    </section>

    <section id="content">
      <!-- 黑马精选 -->
      <section class="hemai_jx">
        <div class="jx_top">
          <div class="jx_tit">
            <img src="/images/icon_5.jpg" alt=""><span>黑马精选</span>
          </div>
          <ul class="jx_tabs">
            <li v-for="(tab, idx) in tabs" :key="idx" :class="{ active: activeTab === idx }"
                @click="activeTab = idx" style="cursor:pointer;">
              <span></span>
              <span class="tab-label" @click.stop="activeTab = idx">{{ tab.name }}</span>
            </li>
          </ul>
        </div>
        <p class="section-desc">精心挑选热门旅游线路，涵盖人气海岛、文化古城、主题探险等多种玩法</p>
        <div class="heima_gn" v-for="(tab, idx) in tabs" :key="idx" v-show="activeTab === idx">
          <div class="guonei_l"><img :src="tab.coverImg" alt=""></div>
          <div class="guone_r">
            <div class="row">
              <div class="col-md-4" v-for="(item, i) in tab.items" :key="i">
                <router-link to="/route-detail">
                  <img :src="item.img" alt="">
                  <div class="has_border">
                    <h3>{{ item.title }}</h3>
                    <div class="price">网付价<em>￥</em><strong>{{ item.price }}</strong><em>起</em></div>
                  </div>
                </router-link>
              </div>
            </div>
          </div>
        </div>
      </section>

      <!-- 国内游 -->
      <section class="hemai_jx">
        <div class="jx_top">
          <div class="jx_tit"><img src="/images/icon_6.jpg" alt=""><span>国内游</span></div>
        </div>
        <p class="section-desc">探索祖国大好河山，从三亚碧海到桂林山水，从丽江古城到北京长城</p>
        <div class="heima_gn">
          <div class="guonei_l"><img src="/images/travel_guilin.jpg" alt="国内游"></div>
          <div class="guone_r">
            <div class="row">
              <div class="col-md-4" v-for="(item, i) in domesticItems" :key="i">
                <router-link to="/route-detail">
                  <img :src="item.img" alt="">
                  <div class="has_border">
                    <h3>{{ item.title }}</h3>
                    <div class="price">网付价<em>￥</em><strong>{{ item.price }}</strong><em>起</em></div>
                  </div>
                </router-link>
              </div>
            </div>
          </div>
        </div>
      </section>

      <!-- 境外游 -->
      <section class="hemai_jx">
        <div class="jx_top">
          <div class="jx_tit"><img src="/images/icon_7.jpg" alt=""><span>境外游</span></div>
        </div>
        <p class="section-desc">走出国门看世界，东南亚风情、海岛度假、欧洲文化之旅</p>
        <div class="heima_gn">
          <div class="guonei_l"><img src="/images/travel_maldives.jpg" alt="境外游"></div>
          <div class="guone_r">
            <div class="row">
              <div class="col-md-4" v-for="(item, i) in overseasItems" :key="i">
                <router-link to="/route-detail">
                  <img :src="item.img" alt="">
                  <div class="has_border">
                    <h3>{{ item.title }}</h3>
                    <div class="price">网付价<em>￥</em><strong>{{ item.price }}</strong><em>起</em></div>
                  </div>
                </router-link>
              </div>
            </div>
          </div>
        </div>
      </section>
    </section>

    <FooterComp />
  </div>
</template>

<script setup>
import { ref, reactive, onMounted, onUnmounted } from 'vue'
import HeaderComp from '@/components/HeaderComp.vue'
import FooterComp from '@/components/FooterComp.vue'

const banners = ['/images/banner_1.jpg', '/images/banner_2.jpg', '/images/banner_3.jpg']
const currentBanner = ref(0)
let timer = null
function nextBanner() { currentBanner.value = (currentBanner.value + 1) % banners.length }
function prevBanner() { currentBanner.value = (currentBanner.value - 1 + banners.length) % banners.length }

const activeTab = ref(0)

const tabs = reactive([
  {
    name: '人气旅游',
    coverImg: '/images/travel_sanya.jpg',
    items: [
      { img: '/images/travel_sanya.jpg', title: '三亚5天4晚自由行 亚龙湾海景酒店+热带天堂森林公园+南山寺', price: 1899 },
      { img: '/images/travel_guilin.jpg', title: '桂林阳朔4天3晚 漓江竹筏漂流+十里画廊骑行+印象刘三姐', price: 1299 },
      { img: '/images/travel_lijiang.jpg', title: '丽江大理6天5晚深度游 玉龙雪山+洱海骑行+束河古镇+泸沽湖', price: 2599 },
      { img: '/images/travel_jiuzhaigou.jpg', title: '九寨沟+黄龙4天3晚 五彩池+诺日朗瀑布+藏族风情体验', price: 2180 },
      { img: '/images/travel_zhangjiajie.jpg', title: '张家界+凤凰古城5天4晚 天门山玻璃栈道+大峡谷+沱江泛舟', price: 1980 },
      { img: '/images/travel_xiamen.jpg', title: '厦门鼓浪屿3天2晚 环岛路骑行+曾厝垵美食街+南普陀寺', price: 1188 },
    ]
  },
  {
    name: '最新旅游',
    coverImg: '/images/travel_beijing.jpg',
    items: [
      { img: '/images/travel_beijing.jpg', title: '北京5天4晚文化之旅 故宫深度游+长城+颐和园+胡同四合院', price: 1999 },
      { img: '/images/travel_xian.jpg', title: '西安4天3晚古都探秘 兵马俑+华清池+大雁塔+回民街美食', price: 1680 },
      { img: '/images/travel_hangzhou.jpg', title: '杭州+苏州4天3晚 西湖泛舟+灵隐寺+拙政园+平江路', price: 1580 },
      { img: '/images/travel_chengdu.jpg', title: '成都4天3晚休闲游 大熊猫基地+宽窄巷子+都江堰+峨眉山', price: 1580 },
      { img: '/images/travel_xishuangbanna.jpg', title: '西双版纳5天4晚 中科院植物园+野象谷+傣族泼水节体验', price: 2380 },
      { img: '/images/travel_qinghai.jpg', title: '青海湖+茶卡盐湖5天4晚 油菜花田+天空之镜+塔尔寺', price: 2680 },
    ]
  },
  {
    name: '主题旅游',
    coverImg: '/images/travel_dunhuang.jpg',
    items: [
      { img: '/images/travel_dunhuang.jpg', title: '丝绸之路8天7晚探秘 敦煌莫高窟+鸣沙山月牙泉+张掖丹霞', price: 3980 },
      { img: '/images/travel_zhangjiajie.jpg', title: '云南秘境8天7晚摄影 元阳梯田+东川红土地+罗平油菜花', price: 3680 },
      { img: '/images/travel_guilin.jpg', title: '贵州黔东南6天5晚 西江千户苗寨+镇远古镇+荔波小七孔', price: 2280 },
      { img: '/images/travel_chengdu.jpg', title: '川西秘境5天4晚自驾 稻城亚丁+新都桥+色达五明佛学院', price: 2880 },
      { img: '/images/travel_jiuzhaigou.jpg', title: '甘南+川北7天6晚 拉卜楞寺+扎尕那+若尔盖草原+九寨沟', price: 3280 },
      { img: '/images/travel_lijiang.jpg', title: '西藏拉萨+林芝8天7晚 布达拉宫+纳木错+雅鲁藏布大峡谷', price: 5980 },
    ]
  },
])

const domesticItems = reactive([
  { img: '/images/travel_sanya.jpg', title: '三亚亚龙湾5天4晚 海景酒店+亲子沙滩+热带水果采摘体验', price: 2188 },
  { img: '/images/travel_guilin.jpg', title: '桂林漓江3天2晚精华游 竹筏漂流+阳朔西街+象鼻山+两江四湖', price: 988 },
  { img: '/images/travel_shanghai.jpg', title: '上海+苏州+杭州5天4晚 迪士尼+外滩+拙政园+西湖+乌镇', price: 2380 },
  { img: '/images/travel_beijing.jpg', title: '北京亲子4天3晚研学 故宫+天文馆+科技馆+长城+烤鸭体验', price: 1780 },
  { img: '/images/travel_lijiang.jpg', title: '丽江+香格里拉5天4晚 虎跳峡+普达措+松赞林寺+古城自由行', price: 2680 },
  { img: '/images/travel_xiamen.jpg', title: '厦门+土楼4天3晚 鼓浪屿+南靖土楼+云水谣+环岛路骑行', price: 1580 },
])

const overseasItems = reactive([
  { img: '/images/travel_bangkok.jpg', title: '泰国曼谷+清迈6天5晚 大皇宫+双龙寺+夜间动物园+泰式按摩', price: 2999 },
  { img: '/images/travel_bali.jpg', title: '巴厘岛5天4晚蜜月之旅 乌布梯田+海神庙+蓝梦岛浮潜+SPA', price: 4580 },
  { img: '/images/travel_maldives.jpg', title: '马尔代夫6天5晚水屋 水上别墅+深潜体验+海豚观赏+日落巡航', price: 8999 },
  { img: '/images/travel_japan.jpg', title: '日本东京+大阪6天5晚 浅草寺+富士山+京都和服体验+大阪美食', price: 5280 },
  { img: '/images/travel_paris.jpg', title: '法国巴黎+瑞士8天7晚 埃菲尔铁塔+卢浮宫+少女峰+日内瓦湖', price: 12800 },
  { img: '/images/travel_bangkok.jpg', title: '越南岘港+会安5天4晚 巴拿山+会安古镇+美溪海滩+越南美食', price: 2380 },
])

onMounted(() => { timer = setInterval(nextBanner, 2000) })
onUnmounted(() => { clearInterval(timer) })
</script>

<style scoped>
.carousel-wrap { position: relative; width: 100%; overflow: hidden; }
.carousel-inner { position: relative; width: 100%; height: 400px; }
.carousel-inner img {
  position: absolute; top: 0; left: 0; width: 100%; height: 100%;
  object-fit: cover; opacity: 0; transition: opacity 0.5s;
}
.carousel-inner img.active { opacity: 1; }
.carousel-indicators { text-align: center; position: absolute; bottom: 15px; width: 100%; z-index: 2; }
.carousel-indicators span {
  display: inline-block; width: 12px; height: 12px; margin: 0 5px;
  background: rgba(255,255,255,0.5); border-radius: 50%; cursor: pointer;
}
.carousel-indicators span.active { background: #fff; }
.carousel-control {
  position: absolute; top: 0; width: 50px; height: 100%; z-index: 2;
  display: flex; align-items: center; justify-content: center;
  font-size: 40px; color: #fff; cursor: pointer; background: rgba(0,0,0,0.15);
  text-decoration: none;
}
.carousel-control.left { left: 0; }
.carousel-control.right { right: 0; }
.carousel-control:hover { background: rgba(0,0,0,0.3); }

:deep(.jx_tabs li) { position: relative; }
:deep(.jx_tabs .tab-label) {
  position: absolute; top: 0; left: 0;
  width: 110px; height: 35px; line-height: 35px;
  text-align: center; z-index: 99; cursor: pointer;
  font-size: 16px; color: #000;
}
:deep(.jx_tabs .active .tab-label) { color: #fff; }

.section-desc {
  margin: 10px 0 15px;
  font-size: 14px;
  color: #666;
  line-height: 1.6;
}

:deep(.guonei_l img) {
  width: 100%;
  height: 100%;
  min-height: 400px;
  object-fit: cover;
  border-radius: 4px;
}
</style>
