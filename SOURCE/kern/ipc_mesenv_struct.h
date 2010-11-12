struct MsgEnv {
MsgEnv_ptr next_Env;
int sender_pid ;
int receiver_pid;
int msg_type;
int msg_size;
int expiry_time;
char *msg_text;
};
