import { createRouter, createWebHistory } from 'vue-router'

const routes = [
  { path: '/', name: 'Home', component: () => import('@/views/HomeView.vue') },
  { path: '/login', name: 'Login', component: () => import('@/views/LoginView.vue') },
  { path: '/register', name: 'Register', component: () => import('@/views/RegisterView.vue') },
  { path: '/register-ok', name: 'RegisterOk', component: () => import('@/views/RegisterOkView.vue') },
  { path: '/route-list', name: 'RouteList', component: () => import('@/views/RouteListView.vue') },
  { path: '/route-detail', name: 'RouteDetail', component: () => import('@/views/RouteDetailView.vue') },
  { path: '/favorite-rank', name: 'FavoriteRank', component: () => import('@/views/FavoriteRankView.vue') },
  { path: '/my-favorite', name: 'MyFavorite', component: () => import('@/views/MyFavoriteView.vue') },
  { path: '/:pathMatch(.*)*', name: 'NotFound', component: () => import('@/views/ErrorView.vue') },
]

const router = createRouter({
  history: createWebHistory(),
  routes,
  scrollBehavior() {
    return { top: 0 }
  }
})

export default router
