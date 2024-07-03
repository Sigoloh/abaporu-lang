<template>
  <main>
    <div class="createNewBlockPopUpContainer" v-if="state.creatingBlock">
      <div class="createNewBlockPopUp">
        <span @click="closeCreateBlock">X</span>
        <h2>Create new block</h2>
        <div class="popUpInput">
          <label>Choose the name of the block</label>
          <input type="input" v-model="state.blockToCreate.name" />
        </div>
        <div class="popUpInput">
          <label>Choose the color of the block</label>
          <input type="color" v-model="state.blockToCreate.color" />
        </div>
        <button @click="createBlock">Create</button>
      </div>
    </div>
    <div class="editorContainer">
      <div class="helpersContainer">
        <div class="helper">
          <h2>Canvas</h2>
          <div class="canvaInput">
            <label for="">Canvas dimension</label>
            <input type="text" v-model="state.size" @change="generateCanva" />
          </div>
          <div class="canvaInput">
            <label for="">Erase all</label>
            <button @click="() => generateCanva(true)">Erase</button>
          </div>
          <div class="canvaInput">
            <label for="">Name your art:</label>
            <input type="text" v-model="state.nameOfTheArt">
            <button @click="compile">Compile</button>
          </div>
        </div>
        <div class="helper">
          <h2 for="">Blocks Pallete</h2>
          <div>
            <div class="palleteSelector">
              <div
                class="colorOption"
                v-for="(name, color) of state.blocks"
                :style="`background: ${color}`"
                :class="{ currentColor: state.selectedColor == color.toString() }"
                @click="() => (state.selectedColor = color.toString())"
                @mouseenter="() => {
                  state.mouseOver = color.toString();
                }"
                @mouseleave="() => {
                  state.mouseOver = '';
                }"
              >
                <div class="colorToolTipContainer" v-if="state.mouseOver === color.toString()">
                    <span class="toolTipText">{{ name }}</span>
                </div>
              </div>
            </div>
          </div>
          <button @click="openCreateBlock">Create new block</button>
        </div>
        <div class="helper">
          <h2>Loop Helper</h2>
          <div>
            <label>Loop range</label>
            <input type="text" v-model="state.loopToCreate">
          </div>
          <button @click="generateLoop">Select Color</button>
        </div>
      </div>
      <div class="canvasOptions">
        <div>
          <h2 for="">Pallete</h2>
          <div class="palleteSelector">
            <div
              class="colorOption"
              v-for="(instruction, key) of state.instructions"
              :style="key === '-' ? `border: 1px solid #c0c0c0` : `background: ${key};`"
              :class="{ currentColor: state.selectedColor == key }"
              @click="() => (state.selectedColor = key)"
              @mouseenter="() => {
                state.mouseOver = key.toString();
              }"
              @mouseleave="() => {
                state.mouseOver = '';
              }"
            >
              <div class="colorToolTipContainer" v-if="state.mouseOver === key.toString()">
                  <span class="toolTipText">{{ instruction }}</span>
              </div>
            </div>
          </div>
        </div>
        <div class="drawCanvas">
          <div class="canvaRow" v-for="(row, i) of state.canvaMatriz">
            <div
              class="canvaPixel"
              :class="{cellCursor: state.selectedColor === '-'}"
              v-for="(pixel, k) of row"
              @click="() => paintPixel(i, k)"
              :style="`background: ${pixel};`"
            ></div>
          </div>
        </div>
      </div>
    </div>
  </main>
</template>
<style scoped>
input{
  background-color: var(--dark);
  border: 1px solid #c0c0c0;
  color: var(--clear);
  font-size: 1.1em;
}
h2{
  margin: 5px 0;
}
button{
  background-color: var(--dark);
  border: 1px solid #c0c0c0;
  color: var(--clear);
  cursor: pointer;
  margin-top: 15px;
  padding: 3px 5px;
}
.cellCursor{
  cursor: cell
}

.helpersContainer{
  display: flex;
  flex-direction: column;
  gap: 10px;
}

.helper{
  border: 1px solid #c0c0c0;
  padding: 20px 5px;
  margin-left: 5px;
  margin-right: 5px;
  max-width: 15vw;
}

.helper input{
  width: 14vw !important;
}

.colorToolTipContainer {
  position: relative;
  display: inline-block;
  border-bottom: 1px dotted black; /* If you want dots under the hoverable text */
}

.colorToolTipContainer .toolTipText {
  min-width: fit-content;
  width: fit-content;
  background-color: black;
  color: #fff;
  text-align: center;
  padding: 5px;
  border-radius: 6px;
  position: absolute;
  z-index: 1;
  top: 10px;
}

.popUpInput {
  display: flex;
  flex-direction: column;
}

.createNewBlockPopUp span {
  width: 100%;
  text-align: right;
  cursor: pointer;
}
.createNewBlockPopUp h2 {
  margin: 0;
}
.createNewBlockPopUp button:hover {
  background: rgb(255, 255, 255, 0.2);
}
.createNewBlockPopUp button {
  background: var(--dark);
  border: 1px solid #c0c0c0;
  color: var(--clear);
  padding: 3px 5px 3px 5px;
  cursor: pointer;
}

.createNewBlockPopUp {
  background: var(--dark);
  max-width: fit-content;
  display: flex;
  flex-direction: column;
  align-items: flex-start;
  justify-content: flex-start;
  gap: 10px;
  padding: 30px;
}
.createNewBlockPopUpContainer {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  position: absolute;
  width: 100%;
  height: 100%;
  top: 0;
  right: 0;
  background: rgb(255, 255, 255, 0.3);
}
.editorContainer {
  display: flex;
  flex-direction: row;
}
.palleteSelector {
  display: flex;
  flex-wrap: wrap;
  margin-bottom: 20px;
  max-width: 30vw;
  gap: 5px;
}
.colorOption {
  height: 20px;
  width: 20px;
  border: 1px solid #c0c0c0;
  cursor: url("../public/paint brush.cur"), auto;
}

.currentColor {
  border: none;
}

.canvaInput {
  display: flex;
  flex-direction: column;
  margin-bottom: 30px;
}

.drawCanvas {
  cursor: url("../public/paint brush.cur"), auto;
  display: flex;
  flex-direction: column;
  gap: 5px;
  max-width: fit-content;
  overflow-y: scroll;
  overflow-x: scroll;
}

.canvaRow {
  display: flex;
  flex-direction: row;
  gap: 5px;
  max-width: fit-content;
}

.canvaPixel {
  border: 1px solid #c0c0c0;
  width: 20px;
  height: 20px;
}
</style>
<script lang="ts">
import { reactive, onBeforeMount } from "vue";
import { toast } from "./main";
export default {
  setup() {
    const state = reactive({
      size: 10,
      canvaMatriz: [] as string[][],
      selectedColor: "#FFFFFF",
      instructions: {
        "#FF0000": "Add One",
        "#0000FF": "Subtract One",
        "#00FF00": "Next Cell",
        "#FFF800": "Previous Cell",
        "#FFFFFF": "Puts Char",
        "#555555": "Puts Value",
        "#FFA500": "End Block",
        "#3FFFE8": "End Loop",
        "-": "Eraser"
      },
      blocks: {} as any,
      creatingBlock: false,
      blockToCreate: {
        name: "" as string,
        color: "" as string,
      },
      mouseOver: '',
      loopToCreate: '',
      nameOfTheArt: ''
    });

    function openCreateBlock() {
      state.creatingBlock = true;
    }

    function onlyNumbers(value: string){
      if(value.match(/\D/gm)){
        return false;
      }
      return true;
    }

    function inLoopRange(value: string){
      if(parseInt(value) < 65535 && parseInt(value) > 0){
        return true;
      }

      return false;
    }

    function generateLoop(){
      if(!onlyNumbers(state.loopToCreate) || !inLoopRange(state.loopToCreate)){
        toast.error('Loop range must be between 1 and 65535');
        return;
      }
      const loopRangeInHex = parseInt(state.loopToCreate).toString(16).padStart(4, '0')
      state.selectedColor = `#11${loopRangeInHex}`;
      toast.success(`I've soaked your brush in ${`#11${loopRangeInHex}`} paint`)
    }

    function createBlock() {
      if (state.blockToCreate.color === "" || state.blockToCreate.name === "") {
        toast.error(
          "In this IDE, blocks must have a name and a color assigned",
        );
        return;
      }
      if (state.instructions[state.blockToCreate.color.toUpperCase()]) {
        toast.error(
          "You cannot use this color as a block because it is an Abapl instruction",
        );
        return;
      }
      state.blocks[state.blockToCreate.color.toUpperCase()] =
        state.blockToCreate.name;
      console.log(state.blocks);
    }

    function closeCreateBlock() {
      state.creatingBlock = false;
      state.blockToCreate = {
        name: "",
        color: "",
      };
    }

    function generateCanva(reset?: boolean) {
      if (reset === true) {
        state.canvaMatriz = [] as string[][];
      }
      for (let i = 0; i < state.size; i++) {
        state.canvaMatriz.push([] as string[]);
        for (let k = 0; k < state.size; k++) {
          if (!state.canvaMatriz[i][k]) {
            state.canvaMatriz[i].push("-");
          }
        }
      }
    }

    function paintPixel(i: number, k: number) {
      state.canvaMatriz[i][k] = state.selectedColor;
    }

    function compile() {
      const stringData = state.canvaMatriz
          .join("")
          .toUpperCase()
          .replace(/\,/gm, "")
          .replace(/\-/gm, "");
      const blob = new Blob([stringData], { type: "text/plain" });

      const url = window.URL.createObjectURL(blob);

      const link = document.createElement("a");

      link.href = url;

      link.download = state.nameOfTheArt.includes('.abapl')?state.nameOfTheArt : state.nameOfTheArt + '.abapl';

      document.body.appendChild(link);

      link.click();
    }

    onBeforeMount(() => {
      generateCanva();
    });

    return {
      onBeforeMount,
      state,
      generateCanva,
      paintPixel,
      compile,
      openCreateBlock,
      closeCreateBlock,
      createBlock,
      inLoopRange,
      onlyNumbers,
      generateLoop
    };
  },
};
</script>
