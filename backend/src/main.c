#include "app.h"
#include "persistence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph fg_graph; FGUser fg_users[128]; size_t fg_user_count; HashTable fg_names; UndoStack fg_undo; FGRequest fg_requests[512]; size_t fg_request_count; int fg_current_user=-1;
char fg_data_dir[256] = "data";
char fg_frontend_dir[256] = "../frontend";

/* O(U+E) for the fixed sample dataset */
int app_seed(void){
    const char *dd = getenv("DATA_DIR");
    if(dd && *dd) snprintf(fg_data_dir, sizeof fg_data_dir, "%s", dd);
    const char *fd = getenv("FRONTEND_DIR");
    if(fd && *fd) snprintf(fg_frontend_dir, sizeof fg_frontend_dir, "%s", fd);

    ensure_data_dir();

    static const char*names[]={"Aarav Mehta","Aisha Khan","Arjun Rao","Diya Patel","Ishaan Gupta","Kavya Nair","Mira Shah","Neel Joshi","Riya Das","Kabir Sen","Anaya Iyer","Dev Malhotra","Sara Thomas","Vivaan Bose","Zoya Ali","Neil Dutta","Tara Menon","Rehan Kapoor","Meera Pillai","Aditya Roy","Anika Sethi","Rohan Jain","Ira Mukherjee","Samar Verma","Nisha Kulkarni","Om Prasad","Kiara Fernandes","Yash Bhat","Sana Qureshi","Aman Gill"};
    static const char*interest[]={"coding","music","reading","design","football","photography","chess","hiking"};
    graph_init(&fg_graph);ht_init(&fg_names,64);stack_init(&fg_undo);
    if(!persistence_load_users(fg_users,&fg_user_count)){
        fg_user_count=30;
        for(size_t i=0;i<fg_user_count;i++){
            snprintf(fg_users[i].name,FG_NAME,"%s",names[i]);
            snprintf(fg_users[i].handle,FG_HANDLE,"student%02lu",(unsigned long)(i+1));
            for(int j=0;j<5;j++)snprintf(fg_users[i].interests[j],32,"%s",interest[(i+j*3)%8]);
            fg_users[i].interest_count=5;
        }
    }
    for(size_t i=0;i<fg_user_count;i++){
        if(add_user(&fg_graph)<0||!ht_put(&fg_names,fg_users[i].handle,(int)i))return 0;
    }
    if(!persistence_load_edges(&fg_graph)){
        for(int base=0;base<(int)fg_user_count;base+=6){
            for(int j=0;j<5&&base+j+1<(int)fg_user_count;j++)add_edge(&fg_graph,base+j,base+j+1);
            if(base+2<(int)fg_user_count)add_edge(&fg_graph,base,base+2);
            if(base+4<(int)fg_user_count)add_edge(&fg_graph,base+1,base+4);
        }
        if(fg_user_count>6)add_edge(&fg_graph,0,6);
        if(fg_user_count>10)add_edge(&fg_graph,4,10);
        if(fg_user_count>12)add_edge(&fg_graph,8,12);
        if(fg_user_count>21)add_edge(&fg_graph,15,21);
        if(fg_user_count>29)add_edge(&fg_graph,23,29);
        persistence_save_edges(&fg_graph);
    }
    persistence_load_requests();
    return 1;
}

/* O(1) outside initialization */
int main(void){
    const char *port_env = getenv("PORT");
    int port = (port_env && *port_env) ? atoi(port_env) : 8080;
    if(!app_seed()){fputs("FRIENDGRAPH data initialization failed\n",stderr);return 1;}
    printf("FRIENDGRAPH C server listening at http://localhost:%d\n", port);
    fflush(stdout);
    return server_run((unsigned short)port);
}

