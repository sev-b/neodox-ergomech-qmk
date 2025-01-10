### How to add new animation:

How to Add a New Animation with Multiple Phases
To add a new animation with multiple phases (similar to pet.c), follow these steps:

1. Generate Animation Data:

   * Use the tool [image2cpp](https://javl.github.io/image2cpp/) to convert your animation frames into a C array format. This tool will output the pixel data for each frame of your animation.
2. Prepare the Animation Data:

   * Copy the output from `image2cpp` and save it to a text file or directly to your clipboard.
3. Run `animation_prep.py`:

   * Open a terminal or command prompt.
   * Navigate to the directory containing `animation_prep.py`.
   * Run the script and paste the image2cpp output when prompted: 
      ```shell
      python animation_prep.py
      ```
   * The script will format the animation data into the required structure.
4. Add the Formatted Data to Your Code:

   * Copy the formatted output from `animation_prep.py`.
   * Open the appropriate animation file (e.g., `loop.c` or `pet.c`).
   * Add the formatted data to the animation array:

      ```c
      static char PROGMEM animations[PHASE_COUNT][OLED_LOOP_MAX_FRAMES][OLED_LOOP_ROWS][OLED_ANIM_SIZE] = {
          {
              // Add your formatted animation frames here
          },
          // Add more phases here
      };
      ```

5. Define Animation Phases:

   * Define the number of frames and the duration for each phase:
      ```c
      #define OLED_MAX_FRAMES 3
      #define FRAME_DURATION 200
      
      #define OLED_ANIMTAION_ROWS 3
      #define OLED_PHASE1_FRAMES 2
      #define OLED_PHASE2_FRAMES 2
      #define OLED_PHASE3_FRAMES 2
      // ect.
      ```
6. Update the Animation Functions:

   * Ensure that the animation functions (`render_animation`, `update_animation_frame`) are correctly called in your code:
      ```c
      static uint8_t animation_frame = 0;
      static uint8_t animation_type  = 0;
      
      void render_this_animation(uint8_t col, uint8_t line) {
          render_animation(col, line, (const char (*)[OLED_ANIM_SIZE])animiations[animation_type], animation_frame, OLED_ANIMTAION_ROWS);
      }
      
      uint32_t animation_phases(uint32_t triger_time, void *cb_arg) {
          static uint32_t anim_frame_duration = FRAME_DURATION;
          switch (current_phase) {
              case 0:
                  animation_type = 0;
                  anim_frame_duration = update_animation_frame(&animation_frame, OLED_PHASE1_FRAMES, FRAME_DURATION);
                  break;
              case 1:
                  animation_type = 1;
                  anim_frame_duration = update_animation_frame(&animation_frame, OLED_PHASE2_FRAMES, FRAME_DURATION);
                  break;
              case 2:
                  animation_type = 2;
                  anim_frame_duration = update_animation_frame(&animation_frame, OLED_PHASE3_FRAMES, FRAME_DURATION);
                  break;
              // Add more cases for additional phases
          }
          return anim_frame_duration;
      }
      ```
7. Update `oled_setup.c`:

   * Make sure to include your animation files in `oled_setup.c`
   * Update the code in `oled_init_user` and `oled_task_user` to call your new phase and render functions accordingly

### Consolidation of: 
* https://github.com/ergohaven/vial-qmk/blob/new-oled-modes/keyboards/ergohaven/ergohaven_oled.c
* https://github.com/qmk/qmk_firmware/pull/12477 
* https://github.com/drashna/qmk_userspace/blob/master/users/drashna/display/oled/oled_stuff.c#L852
