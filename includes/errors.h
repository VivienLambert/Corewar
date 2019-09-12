/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:55:22 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/29 13:33:37 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/*
**  Please update ERR_TYPE_NBR when adding a new error
*/
# define ERR_TYPE_NBR    13

/*
**  Errors message max size: Respect it or upload unless you want to segfault
*/
# define ERR_MSG_SIZE		300

/*
**  Errors define code
**  Please update ERR_TYPE_NBR when adding a new error
**  ERR_DBLDUMP		Two dump val precised
**  ERR_DUMPVAL		Wrong dump val
**  ERR_BADARG		Unknown arguments
**  ERR_BADNBR		Bad player number
**  ERR_NOCHAMP		No champions given in arguments
**	ERR_TMCHAMP		Too much chaipions as argument refer to MAX_PLAYERS in op.h
**  ERR_TWONBR		Two player numbers
**  ERR_OPEN		File opening error
**  ERR_CHAMP		Invalid champ(header)
**  ERR_SIZE		Invalid champ(size): please specify champ name in message
**  ERR_MALLOC		Malloc error: please precced err message by file/function
**  ERR_NCURSE		NCurse failed
*/

# define USAGE				0
# define ERR_DBLDUMP		1
# define ERR_DUMPVAL		2
# define ERR_BADARG			3
# define ERR_BADNBR			4
# define ERR_NOCHAMP		5
# define ERR_TMCHAMP		6
# define ERR_TWONBR			7
# define ERR_OPEN			8
# define ERR_CHAMP			9
# define ERR_SIZE			10
# define ERR_MALLOC			11
# define ERR_NCURSE			12

#endif
