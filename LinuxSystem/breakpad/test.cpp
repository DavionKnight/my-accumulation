#include <iostream>
#include "src/client/linux/handler/exception_handler.h"
//#include "../breakpad/src/third_party/lss/linux_syscall_support.h"
//#include "../breakpad/src/client/linux/handler/minidump_descriptor.h"
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <future>

#define NAME_MAX 255
static bool dumpCallback(const google_breakpad::MinidumpDescriptor &descriptor, void *context, bool succeeded)
{
    printf("Dump path: %s\n", descriptor.path());
    auto mainThreadId = std::this_thread::get_id();
    char line[NAME_MAX];

    snprintf(line, NAME_MAX, "/proc/%ld/comm",sys_getpid() );
    int fd = sys_open(line, O_RDONLY, 0);
    ssize_t read_len = sys_read(fd, line, NAME_MAX - 1);
    sys_close(fd);
    line[read_len - 1] = 0;
    printf("this thread is : %s\n", line);

    return succeeded;
}


static void crashHare()
{
    int *a = (int *)(NULL);
    *a = 1; // 放心的奔溃吧
}


int main(int argc, char *argv[])
{
    google_breakpad::MinidumpDescriptor descriptor("./tmp");
    google_breakpad::ExceptionHandler eh(descriptor, NULL, dumpCallback, NULL, true, -1);

    std::thread t(crashHare);

    t.join();

    return 0;
}

