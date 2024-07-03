import "./assets/main.css";
import Toast, { useToast } from "vue-toastification";
import { createApp } from "vue";
import App from "./App.vue";

const app = createApp(App);
const options = {};
app.use(Toast, options);
export const toast = useToast();
app.mount("#app");
