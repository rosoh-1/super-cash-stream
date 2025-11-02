# Super Cash Stream

Sistema di streaming di log cash con Fluentd, Redis Streams e API Node.js.

## Architettura

- **Simulator** : Crea file in formato json 
- **Fluentd**: Legge il file di log `cash.log` e invia gli eventi via HTTP
- **API Node.js**: Riceve gli eventi da Fluentd e li scrive su Redis Stream
- **Redis**: Memorizza gli eventi in un Redis Stream per elaborazione successiva

## Avvio

```bash
docker-compose up -d
```
## Utilizzo

### Leggere gli eventi da Redis Stream

Connettiti a Redis:
```bash
docker exec -it redis redis-cli
```

Comandi utili:
```bash
# Leggi tutti gli eventi
XRANGE super-cash-stream - +

# Conta gli eventi
XLEN super-cash-stream

# Leggi gli ultimi 10 eventi
XREVRANGE super-cash-stream + - COUNT 10

# Leggi nuovi eventi in tempo reale
XREAD BLOCK 0 STREAMS super-cash-stream $
```
