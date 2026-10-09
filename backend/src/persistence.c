#include "persistence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
static void make_dir(const char* path) { _mkdir(path); }
#else
#include <sys/stat.h>
static void make_dir(const char* path) { mkdir(path, 0755); }
#endif

static void copy_file(const char* src, const char* dst) {
    FILE *in = fopen(src, "rb");
    if (!in) return;
    FILE *out = fopen(dst, "wb");
    if (!out) { fclose(in); return; }
    char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, in)) > 0) {
        fwrite(buf, 1, n, out);
    }
    fclose(in);
    fclose(out);
}

void ensure_data_dir(void) {
    make_dir(fg_data_dir);
    const char* files[] = {"users.csv", "edges.csv", "requests.csv"};
    for (int i = 0; i < 3; i++) {
        char path[512];
        snprintf(path, sizeof path, "%s/%s", fg_data_dir, files[i]);
        FILE *f = fopen(path, "r");
        if (f) {
            fclose(f);
        } else if (strcmp(fg_data_dir, "data") != 0) {
            char src[512];
            snprintf(src, sizeof src, "data/%s", files[i]);
            copy_file(src, path);
        }
    }
}

/* O(U*I), with fixed-width CSV rows and I interests per user */
int persistence_load_users(FGUser*users,size_t*count){
    char path[512]; snprintf(path, sizeof path, "%s/users.csv", fg_data_dir);
    FILE*f=fopen(path,"r");if(!f)return 0;char line[512];size_t n=0;fgets(line,sizeof line,f);while(fgets(line,sizeof line,f)&&n<128){line[strcspn(line,"\r\n")]=0;char*id=strtok(line,",");char*handle=strtok(NULL,",");char*name=strtok(NULL,",");char*interests=strtok(NULL,",");if(!id||!handle||!name||!interests||atoi(id)!=(int)n)continue;snprintf(users[n].handle,FG_HANDLE,"%s",handle);snprintf(users[n].name,FG_NAME,"%s",name);char*token=strtok(interests,"|");while(token&&users[n].interest_count<FG_INTERESTS){snprintf(users[n].interests[users[n].interest_count++],32,"%s",token);token=strtok(NULL,"|");}n++;}fclose(f);*count=n;return n>0;
}
/* O(E) */ int persistence_load_edges(Graph*g){
    char path[512]; snprintf(path, sizeof path, "%s/edges.csv", fg_data_dir);
    FILE*f=fopen(path,"r");if(!f)return 0;char line[128];int count=0;fgets(line,sizeof line,f);while(fgets(line,sizeof line,f)){int a,b;if(sscanf(line,"%d,%d",&a,&b)==2&&add_edge(g,a,b)>0)count++;}fclose(f);return count>0;
}
/* O(E) */ int persistence_save_edges(const Graph*g){
    char path[512]; snprintf(path, sizeof path, "%s/edges.csv", fg_data_dir);
    FILE*f=fopen(path,"w");if(!f)return 0;fputs("from,to\n",f);for(size_t i=0;i<g->n;i++)for(size_t j=0;j<g->adj[i].len;j++)if(g->adj[i].items[j]>(int)i)fprintf(f,"%zu,%d\n",i,g->adj[i].items[j]);int ok=!ferror(f);fclose(f);return ok;
}
/* O(R) */ int persistence_load_requests(void){
    char path[512]; snprintf(path, sizeof path, "%s/requests.csv", fg_data_dir);
    FILE*f=fopen(path,"r");if(!f)return 0;char line[128];fg_request_count=0;fgets(line,sizeof line,f);while(fgets(line,sizeof line,f)&&fg_request_count<512){FGRequest r;if(sscanf(line,"%d,%d,%d,%d",&r.id,&r.from,&r.to,&r.status)==4){fg_requests[fg_request_count++]=r;if(r.status==-1&&r.from>=0&&(size_t)r.from<fg_user_count&&fg_users[r.from].declined_count<128)fg_users[r.from].declined[fg_users[r.from].declined_count++]=r.to;}}fclose(f);return 1;
}
/* O(R) */ int persistence_save_requests(void){
    char path[512]; snprintf(path, sizeof path, "%s/requests.csv", fg_data_dir);
    FILE*f=fopen(path,"w");if(!f)return 0;fputs("id,from,to,status\n",f);for(size_t i=0;i<fg_request_count;i++)fprintf(f,"%d,%d,%d,%d\n",fg_requests[i].id,fg_requests[i].from,fg_requests[i].to,fg_requests[i].status);int ok=!ferror(f);fclose(f);return ok;
}

