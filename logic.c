#include "mshell.h"
#include <unistd.h>

void    logic(t_data *data)
{
    char dir[66];

    if (!ft_strncmp(data->bin, "pwd", 3))
        getcwd(dir, 66);
        printf("%s\n", dir);
}