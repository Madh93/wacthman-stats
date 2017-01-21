# Watchman Stats

Stats server for [Watchman](https://github.com/Madh93/watchman).

### To do

- [x] Recibir un resumen de las estadísticas cada cierto tiempo.
- [x] **Opcional:** Comunicación bidireccional entre el servidor y el cliente.
- [x] **Opcional:** Varios procesos o demonios cliente que envían información a un servidor.
- [x] **Opcional:** Convertir en un demonio el código del servidor.


### Installation

    git clone https://github.com/Madh93/watchman-stats && cd watchman-stats
    make
    sudo make install

### Usage

    watchman-stats [options]

Start service using default settings:

    service watchman-stats start

Defaults settings are available in `/etc/default/watchman-stats.conf`:

    WATCHMAN_STATS_ARGS="--port 12345"

You can edit or override arguments:

    service watchman-stats start --port 7635

(If no port is passed `watchman-stats` set up defaults: `12345`).

##### Logs

Logs are available in `/var/log/watchman-stats.log`:

    tail -f /var/log/watchman-stats.log

    Jan 21 08:41:23 ubuntu watchman-stats[1436]: Starting...
    Jan 21 08:41:23 ubuntu watchman-stats[1436]: Started watchman-stats
    Jan 21 08:41:23 ubuntu watchman-stats[1436]: Started server in port 12345
    Jan 21 08:41:49 ubuntu watchman-stats[1436]: New connection from 127.0.0.1
    Jan 21 08:41:49 ubuntu watchman-stats[1436]: Client says: Hello world from Watchman client!
    Jan 21 08:42:01 ubuntu watchman-stats[1436]: New connection from 127.0.0.1
    Jan 21 08:42:01 ubuntu watchman-stats[1436]: Client says: Hello world from Watchman client!
    Jan 21 08:42:04 ubuntu watchman-stats[1436]: Client says: New event registered!
    Jan 21 08:42:04 ubuntu watchman-stats[1436]: Client says: New event registered!
    Jan 21 08:42:28 ubuntu watchman-stats[1436]: Client has disconnected
    Jan 21 08:42:42 ubuntu watchman-stats[1436]: Client has disconnected
