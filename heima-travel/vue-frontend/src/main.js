import './assets/css/bootstrap.min.css'
import './assets/css/bootstrap-theme.min.css'
import { createApp } from 'vue'
import { createPinia } from 'pinia'
import App from './App.vue'
import router from './router'
import './assets/css/common.css'
import './assets/css/index.css'
import './assets/css/login.css'
import './assets/css/register.css'
import './assets/css/search.css'
import './assets/css/route-detail.css'
import './assets/css/ranking-list.css'

const app = createApp(App)
const pinia = createPinia()
app.use(pinia)
app.use(router)
app.mount('#app')
