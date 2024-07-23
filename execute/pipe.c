/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:14:19 by relamine          #+#    #+#             */
/*   Updated: 2024/07/23 19:10:49 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h> 
// #include <unistd.h> 
// #include <stdlib.h>

// #define MSGSIZE 16 
// char* msg1 = "hello, world #1"; 
// char* msg2 = "hello, world #2"; 
// char* msg3 = "hello, world #3"; 
  
// int main() 
// { 
//     char inbuf[MSGSIZE]; 
//     int p[2], i; 
  
//     if (pipe(p) < 0) 
//         exit(1); 
  
//     /* continued */
//     /* write pipe */
  
//     write(p[1], msg1, MSGSIZE); 
//     write(p[1], msg2, MSGSIZE); 
//     write(p[1], msg3, MSGSIZE); 
// 	dup(p[0], 0);
//     for (i = 0; i < 3; i++) { 
//         /* read pipe */
//         read(p[0], inbuf, MSGSIZE); 
//         printf("%s\n", inbuf); 
//     } 
//     return 0; 
// } 


