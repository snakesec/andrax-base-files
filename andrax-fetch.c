/*
*******************************************************************************
*                                                                             *
* Copyright 2026 Weidsom Nascimento - SNAKE Security                          *
*                                                                             *
* Licensed under the Apache License, Version 2.0 (the "License");             *
* you may not use this file except in compliance with the License.            *
* You may obtain a copy of the License at                                     *
*                                                                             *
*     http://www.apache.org/licenses/LICENSE-2.0                              *
*                                                                             *
* Unless required by applicable law or agreed to in writing, software         *
* distributed under the License is distributed on an "AS IS" BASIS,           *
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.    *
* See the License for the specific language governing permissions and         *
* limitations under the License.                                              *
*                                                                             *
*******************************************************************************
*/

/*
*
* I know, this code is a mess and needs comments, but I don't usually comment
* out my code in detail. This is a simple program based on the now-defunct
* NEOFETCH, but hardcoded for ANDRAX-NG.
*
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define DIM_BLACK   "\033[0;30m"
#define DIM_RED     "\033[0;31m"
#define DIM_GREEN   "\033[0;32m"
#define DIM_YELLOW  "\033[0;33m"
#define DIM_BLUE    "\033[0;34m"
#define DIM_MAGENTA "\033[0;35m"
#define DIM_CYAN    "\033[0;36m"
#define DIM_WHITE   "\033[0;37m"

#define BRIGHT_BLACK   "\033[1;90m"
#define BRIGHT_RED     "\033[1;91m"
#define BRIGHT_GREEN   "\033[1;92m"
#define BRIGHT_YELLOW  "\033[1;93m"
#define BRIGHT_BLUE    "\033[1;94m"
#define BRIGHT_MAGENTA "\033[1;95m"
#define BRIGHT_CYAN    "\033[1;96m"
#define BRIGHT_WHITE   "\033[1;97m"

#define RESET "\033[0m"

// Take a look at how beautiful the ANDRAX-NG logo is:
const char *logo[] = {
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠒⢦⣤⣀⠈⠑⠶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⣿⣦⣀⠈⣻⣿⣦⣄⡀⠀⠀⠐⢤⡀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣴⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣾⣿⣦⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠐⢉⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣤⣌⡻⢿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⠉⠉⠛⠛⠿⢿⣿⣿⣿⣿⣿⣋⣳⣦⣤⣶⣦⡀",
"⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡜⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⡀⠀⠀⠈⠻⢿⣿⣿⣿⣿⣿⣿⣿⣧⠁",
"⠀⣾⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠙⠻⠿⠿⠿⠛⠛⠛⠻⠿⣿⣿⣿⣷⣄⡀⠀⠀⠉⠙⢻⡿⠿⠿⣿⠇⠀",
"⠘⠁⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢿⣿⣿⣶⣄⡀⠀⠈⠀⠀⠀⠉⠀⠀",
"⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠿⠿⠿⠶⠖⠂⠀⠀⠀ ",
"⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⣿⠋⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠹⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⠿⠟⠛⠋⠉⠉⠉⠉⠛⠛⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⠿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠿⢿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⠀⠀⠀⠀⠀  ",

};

// The function name is self-explanatory!
int get_utf8_visible_width(const char *str) {
    int width = 0;
    while (*str) {
        if ((*str & 0x80) == 0)          { width++; str++; }
        else if ((*str & 0xE0) == 0xC0) { width++; str += 2; }
        else if ((*str & 0xF0) == 0xE0) { width++; str += 3; }
        else if ((*str & 0xF8) == 0xF0) { width += 2; str += 4; }
        else                            { str++; }
    }
    return width;
}

// This function ensures (sort of) that the logo and strings do not exceed the maximum size of the box
int printf_utf8_clipped(const char *str, int max_visible_width) {
    int current_width = 0;
    
    while (*str && current_width < max_visible_width) {
        if (*str == '\033') { 
            const char *seq_start = str;
            str++;
            
            if (*str == '[') {
                str++;
                while (*str && (*str < 0x40 || *str > 0x7E)) {
                    str++;
                }
                if (*str) str++;
            }
            
            fwrite(seq_start, 1, str - seq_start, stdout);
            continue;
        }

        int bytes = 0;
        int char_width = 0;

        if ((*str & 0x80) == 0)          { bytes = 1; char_width = 1; }
        else if ((*str & 0xE0) == 0xC0) { bytes = 2; char_width = 1; }
        else if ((*str & 0xF0) == 0xE0) { bytes = 3; char_width = 1; }
        else if ((*str & 0xF8) == 0xF0) { bytes = 4; char_width = 2; }
        else                            { bytes = 1; char_width = 0; }

        if (current_width + char_width > max_visible_width) break; 

        fwrite(str, 1, bytes, stdout);
        current_width += char_width;
        str += bytes;
    }
    
    return current_width;
}

// This function is broken, but somehow it still works...
int count_utf8_clipped(const char *str, int max_visible_width) {
    int current_width = 0;
    
    while (*str && current_width < max_visible_width) {
        if (*str == '\033') { 
            const char *seq_start = str;
            str++;
            
            if (*str == '[') {
                str++;
                while (*str && (*str < 0x40 || *str > 0x7E)) {
                    str++;
                }
                if (*str) str++; 
            }
            
            continue;
        }

        int bytes = 0;
        int char_width = 0;

        if ((*str & 0x80) == 0)          { bytes = 1; char_width = 1; }
        else if ((*str & 0xE0) == 0xC0) { bytes = 2; char_width = 1; }
        else if ((*str & 0xF0) == 0xE0) { bytes = 3; char_width = 1; }
        else if ((*str & 0xF8) == 0xF0) { bytes = 4; char_width = 2; }
        else                            { bytes = 1; char_width = 0; }

        if (current_width + char_width > max_visible_width) break; 

        current_width += char_width;
        str += bytes;
    }
    
    return current_width;
}

// I could use libsqlite3 to do this count, but this "hack" is simpler and uglier and I like ugly code!
int get_afos_package_count(void) {
    const char *cmd = "sqlite3 \"/opt/AFOS/pkg.db\" \"SELECT COUNT(*) FROM PACKAGES;\" 2>/dev/null";
    char buffer[32];
    int count = -1;

    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        count = atoi(buffer);
    }

    pclose(fp);

    return count;
}

int get_apt_package_count(void) {
    const char *cmd = "dpkg -l | grep -c \"^ii\" 2>/dev/null";
    char buffer[32];
    int count = -1;

    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        count = atoi(buffer);
    }

    pclose(fp);

    return count;
}

long get_cached_ram() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) return 0;

    char label[32];
    long value = 0;
    
    while (fscanf(fp, "%31s %ld kB", label, &value) != EOF) {
        if (strcmp(label, "Cached:") == 0) {
            fclose(fp);
            return value * 1024;
        }
    }

    fclose(fp);
    return 0;
}

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int term_w = w.ws_col;

    struct utsname sys;
    struct sysinfo sys_info;
    
    uname(&sys);
    sysinfo(&sys_info);
    
    char *user = getlogin();
    if (!user) user = "andrax"; 
    
    char hostname[64];
    gethostname(hostname, sizeof(hostname));

    long total_seconds = sys_info.uptime;
    long days = total_seconds / 86400;
    long hours = (total_seconds % 86400) / 3600;
    long minutes = (total_seconds % 3600) / 60;
    long seconds = total_seconds % 60;

    long multiplier = sys_info.mem_unit; 
    
    long total_ram = (sys_info.totalram * multiplier) / 1000 / 1000;
    long free_ram  = (sys_info.freeram * multiplier) / 1000 / 1000;
    long buffer_ram = (sys_info.bufferram * multiplier) / 1000 / 1000;
    long shared_ram = (sys_info.sharedram * multiplier) / 1000 / 1000;

    long cached_ram = get_cached_ram() / 1000 / 1000;

    long used_ram = total_ram - free_ram - cached_ram - buffer_ram;

    char info[13][128];
    sprintf(info[0], "%s%s%s@%s%s%s", BRIGHT_BLUE, user, BRIGHT_CYAN, BRIGHT_GREEN, hostname, RESET);
    sprintf(info[1], "-----------------------");
    sprintf(info[2], " ");
    sprintf(info[3], "%sMachine%s: %s", BRIGHT_RED, RESET, sys.machine);
    sprintf(info[4], "%sMem%s: %s%ld%s/%ldMB", BRIGHT_RED, RESET, BRIGHT_YELLOW, used_ram, RESET, total_ram);
    sprintf(info[5], "%sOS%s: ANDRAX-NG (Linux)", BRIGHT_RED, RESET);
    sprintf(info[6], "%sKernel%s: %s", BRIGHT_RED, RESET, sys.release);
    sprintf(info[7], "%sUptime%s: %ld Days, %ld:%ld:%ld", BRIGHT_RED, RESET, days, hours, minutes, seconds);
    sprintf(info[8], " ");
    sprintf(info[9], "%sAFOS-NG%s: %d %sAPT%s: %d", BRIGHT_WHITE, RESET, get_afos_package_count(), BRIGHT_WHITE, RESET, get_apt_package_count());
    sprintf(info[10], " ");
    sprintf(info[11], "%s██%s██%s██%s██%s██%s██%s██%s██", DIM_BLACK, DIM_RED, DIM_GREEN, DIM_YELLOW, DIM_BLUE, DIM_MAGENTA, DIM_CYAN, DIM_WHITE);
    sprintf(info[12], "%s██%s██%s██%s██%s██%s██%s██%s██", BRIGHT_BLACK, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW, BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_WHITE);
    
    

    int logo_h = sizeof(logo) / sizeof(logo[0]);
    int info_h = sizeof(info) / sizeof(info[0]);

    int max_logo_visible_w = 0;
    for(int i=0; i<logo_h; i++) {
        int vw = get_utf8_visible_width(logo[i]);
        if(vw > max_logo_visible_w) max_logo_visible_w = vw;
    }

    int max_info_w = 0;
    for(int i=0; i<info_h; i++) {
        if (i == 1) continue;
        int len = count_utf8_clipped(info[i], (max_logo_visible_w > max_info_w) ? max_logo_visible_w : max_info_w < term_w );
        if(len > max_info_w) max_info_w = len;
    }

    int box_w;
    if (term_w < 80) {
        int max_w = (max_logo_visible_w > max_info_w) ? max_logo_visible_w : max_info_w;
        box_w = (max_w < term_w - 6) ? max_w : term_w - 6;
    } else {
        int gap = 4;
        int desired_w = max_logo_visible_w + gap + max_info_w;
        box_w = (desired_w < term_w - 6) ? desired_w : term_w - 6;
    }

    printf("\n " BRIGHT_RED "┏");
    for (int i = 0; i < box_w + 2; i++) printf("━");
    printf("┓" RESET "\n");

    printf(" " BRIGHT_RED "┃ " RESET);
    for (int i = 0; i < box_w; i++) printf(" ");
    printf(BRIGHT_RED " ┃" RESET "\n");

    if (term_w < 80) {
        for (int i = 0; i < logo_h; i++) {
            printf(" " BRIGHT_RED "┃ " RESET);
            
            int logo_len = get_utf8_visible_width(logo[i]);
            if (logo_len > box_w) logo_len = box_w;
            
            int left_pad = (box_w - logo_len) / 2;
            int visible_len = 0;

            for (int p = 0; p < left_pad; p++) { printf(" "); visible_len++; }

            printf(BRIGHT_GREEN);
            visible_len += printf_utf8_clipped(logo[i], box_w - visible_len);
            printf(RESET);

            while (visible_len < box_w) { printf(" "); visible_len++; }
            printf(BRIGHT_RED " ┃" RESET "\n");
        }

        printf(" " BRIGHT_RED "┃ " RESET);
        int text_block_pad = (box_w - max_info_w) / 2;
        int current_div_len = 0;

        for (int p = 0; p < text_block_pad; p++) { printf(" "); current_div_len++; }
        for (int d = 0; d < max_info_w + 2; d++)     { printf("-"); current_div_len++; }
        while (current_div_len < box_w)          { printf(" "); current_div_len++; }
        printf(BRIGHT_RED " ┃" RESET "\n");

        for (int i = 0; i < info_h; i++) {
            if (i == 1) continue;

            printf(" " BRIGHT_RED "┃  " RESET);
            int visible_len = 0;

            for (int p = 0; p < text_block_pad; p++) { printf(" "); visible_len++; }
            
            int remaining = box_w - visible_len;
            visible_len += printf_utf8_clipped(info[i], box_w - visible_len - 1);
            
            while (visible_len < box_w - 1) { printf(" "); visible_len++; }
            printf(BRIGHT_RED " ┃" RESET "\n");
        }

    } else {
        int max_rows = (logo_h > info_h) ? logo_h : info_h;
        int gap = 1;

        for (int i = 0; i < max_rows; i++) {
            printf(" " BRIGHT_RED "┃ " RESET);
            int current_row_visible_len = 0;

            if (i < logo_h) {
                printf(BRIGHT_GREEN);
                int allowed_logo_w = (max_logo_visible_w < box_w) ? max_logo_visible_w : box_w;
                current_row_visible_len += printf_utf8_clipped(logo[i], allowed_logo_w);
                printf(RESET);
            }

            int target_gap = max_logo_visible_w + gap;
            while (current_row_visible_len < target_gap && current_row_visible_len < box_w) {
                printf(" ");
                current_row_visible_len++;
            }

            if (i < info_h && current_row_visible_len < box_w) {
                int remaining = box_w - current_row_visible_len;

                const char* big_line = "-----------------------------------------------------------------";

                if (i == 1) {
                    printf("%.*s", remaining, big_line);
                    int info_len = strlen(big_line);
                    current_row_visible_len += (info_len > remaining) ? remaining : info_len;
                } else {
                    current_row_visible_len += printf_utf8_clipped(info[i], remaining);
                }
                
            }

            while (current_row_visible_len < box_w) { 
                printf(" "); 
                current_row_visible_len++; 
            }
            printf(BRIGHT_RED " ┃" RESET "\n");
        }
    }

    printf(" " BRIGHT_RED "┃ " RESET);
    for (int i = 0; i < box_w; i++) printf(" ");
    printf(BRIGHT_RED " ┃" RESET "\n");

    printf(" " BRIGHT_RED "┗");
    for (int i = 0; i < box_w + 2; i++) printf("━");
    printf("┛" RESET "\n\n");

    return 0;
}