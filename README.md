To-do minishell:

Done:
- Display a prompt whem waiting for a new command
- Have a working history
- Search and launch the right executable (based on PATH) (fonctionne pour l'instant que si on met une seule cmd)
- Handle ctrl-C, ctrl-D and ctrl-\ (a verifier dans le cas d'un pipe)
- pwd
- env
- exit
- echo with option -n (and $VAR)
- cd (absolute or relative path)
- Checker before parsing
- unset
- export
- Handle single quote
- Handle double quote
- Implement redirections (<,>,<<,>>)
- Implement pipes (a adapter par rapport a ce qu'on a)
- Handle environment variables
- Handle $?
- export
- Implement wildcard (*) as working directory
- Implement && and || with parenthesis for priorities
