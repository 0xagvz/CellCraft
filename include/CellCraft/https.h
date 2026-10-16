#ifndef _HTTPS_H
#define _HTTPS_H
#include "config.h"
#ifdef ONLINE_MODE_AUTH
#include "player.h"
typedef struct player_t player_t;
struct httpsData_t
{
    player_t *currentPlayer;
    mbedtls_net_context net;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;
    size_t timeout; // timeout in ticks
    size_t len;
    size_t offset;

    uint8_t connection_closed : 1;
    char buffer[2048];
};
typedef struct httpsData_t httpsData_t;
httpsData_t *httpsGetData();
int httpsConnect(player_t *currentPlayer, const char *hostname, const char *port);
void httpsGetPlayerInfo(player_t *currentPlayer);
int httpsRtr(player_t *currentPlayer);
int httpsRts(player_t *currentPlayer);
void httpsFreePlayer(player_t *currentPlayer);
void httpsCleanup();
#endif /*ONLINE_MODE_AUTH*/
#endif