import { reactive } from "vue";
import type { Block } from "./types/Block";

export const globalState = reactive({
  createdBlocks: [] as Block[],
  selectedColor: "",
});
