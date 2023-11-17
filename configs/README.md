# Configuração básica - Single Board HPC Cluster

## Passo 0: Preparação do hardware
Como alternativa, iremos alterar o Raspberry Pi pelo Orange Pi, a fim de buscar por imcompatibilidades durante a construção do cluster.

- 3x Orange Pi Pc 
- 1x Raspberry Pi 3 Model B
- 4x MicroSD Cards
- 4x Fontes/Cabos de força
- 1x Switch 8-portas 10/100/1000
- 1x Pen Drive 64GB (estamos usando um menor com 16GB)
- Cabos de rede _Cat5e_

## Passo 01: Instalação do Sistema Operacional
Durante essa etapa, basta seguir as instruções de **[outro tutorial](https://github.com/Prisma-IAP/basic_network_configs)** presente neste repositório para a instalação do sistema operacional e definição dos _hostnames_ de cada computador.

**_Obs_**: Durante a definição de hostnames, de preferência para nomes sem espaços, ex: _node01_, _node02_, _node03_, _node04_.

## Passo 02: Sincronização de data/hora

O _SLURM_ e o _MUNGE_ necessitam que as configurações de data/hora estejam devidamente sincronizadas, para esta etapa basta realizar a seguinte instalação: 

```shell
sudo apt install ntpdate -y
```

Ao término do processo, basta reiniciar cada computador.
