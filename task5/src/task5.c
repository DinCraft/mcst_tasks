#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// не нашёл sys_errlist, поэтому сохранил названия макросов в виде функции
const char* errno_name(int err) {
  switch(err) {
    case EPERM: return "EPERM";
    case ENOENT: return "ENOENT";
    case ESRCH: return "ESRCH";
    case EINTR: return "EINTR";
    case EIO: return "EIO";
    case ENXIO: return "ENXIO";
    case E2BIG: return "E2BIG";
    case ENOEXEC: return "ENOEXEC";
    case EBADF: return "EBADF";
    case ECHILD: return "ECHILD";
    case EAGAIN: return "EAGAIN";
    case ENOMEM: return "ENOMEM";
    case EACCES: return "EACCES";
    case EFAULT: return "EFAULT";
    case EBUSY: return "EBUSY";
    case EEXIST: return "EEXIST";
    case EXDEV: return "EXDEV";
    case ENODEV: return "ENODEV";
    case ENOTDIR: return "ENOTDIR";
    case EISDIR: return "EISDIR";
    case EINVAL: return "EINVAL";
    case ENFILE: return "ENFILE";
    case EMFILE: return "EMFILE";
    case ENOTTY: return "ENOTTY";
    case EFBIG: return "EFBIG";
    case ENOSPC: return "ENOSPC";
    case ESPIPE: return "ESPIPE";
    case EROFS: return "EROFS";
    case EMLINK: return "EMLINK";
    case EPIPE: return "EPIPE";
    case EDOM: return "EDOM";
    case ERANGE: return "ERANGE";
    default: return "UNKNOWN";
  }
}

void print_error(int error) {
  perror("Error opening file");
  printf("Errno = %s(%d)\n", errno_name(error), error);
}

int main(int argc, char *argv[])
{
  char *file_name = "file.txt";
  int fd = open(file_name, O_RDONLY, S_IRWXU);
  int error = errno;
  if (fd == -1) {
    print_error(error);
    return -1;
  }
  int result = close(fd);
  error = errno;
  if (result == -1) {
    print_error(error);
    return -1;
  }
  return 0;
}
