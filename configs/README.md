# Configuração básica - Single Board HPC Cluster

## Passo 00: Preparação do hardware
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

## Passo 03: Preparação do armazenamento compartilhado
- Conecte o pen drive no _node01_ que será definido como _Node Master_

- Acesse o _node01_ através de outro terminal de forma remota

- Identifique as informações do dispositivo móvel com o comando a seguir:
```shell
lsblk
```
- Provavelmente o caminho do dispositivo será _/dev/sda1_

- Realize a formatação do pen drive com o comando a seguir:
```shell
sudo mkfs.ext4 /dev/sda1
```

- Crie um novo diretório que servirá como ponto de montagem entre todos os nós, para isso, siga as instruções abaixo:
```shell
sudo mkdir /clusterfs
sudo chown nobody.nogroup -R /clusterfs
sudo chmod 777 -R /clusterfs
```

- Encontre as informações de UUID do ponto _/dev/sda1_, para isso, utilize o comando a seguir:
```shell
blkid
```

- Resultado será parecido com o demonstrado a seguir:
```shell
/dev/sda1: UUID="017c30aa-4589-4ccb-a8b5-44d2834f8af8"
```

- A seguir edite o arquivo ***/etc/fstab***, adicionando o UUID e outras informações de acordo com o exemplo abaixo
```shell
UUID=017c30aa-4589-4ccb-a8b5-44d2834f8af8 /clusterfs ext4 defaults 0 2
```

- Por fim, monte a unidade com o comando a seguir:
```shell
sudo mount -a
```

- Antes de finalizar esta etapa, é importante definir algumas permissões de acordo com os comandos a seguir:
```shell
sudo chown nobody.nogroup -R /clusterfs
sudo chmod -R 766 /clusterfs
```

## Passo 04: Configuração NFS (Network File System)

### Passo 04.01: Instalação do NFS Server
- Realize o processo de instalação no ***node01*** com o comando a seguir:
```shell
sudo apt install nfs-kernel-server -y
```

- Edite o arquivo _/etc/exports_ e adicione a linha abaixo:
```shell
/clusterfs    <ip addr>(rw,sync,no_root_squash,no_subtree_check)
```

- Substitua o _<ip addr>_ pelo endereço IP inicial da sua rede, dessa forma, qualquer outro computador poderá acessar o ponto de montagem. Por exemplo, se os endereços da sua LAN forem no padrão _192.168.1.X_, o resultado será conforme abaixo:
```shell
/clusterfs 192.168.1.0/24(rw,sync,no_root_squash,no_subtree_check)
```

- Por fim, atualize o NFS kernel server com o comando a seguir:
```shell
sudo exportfs -a
```

### Passo 04.02: Instalação do NFS Client
- Realize o processo de instalação nos outros ***nodes*** com o comando a seguir:
```shell
sudo apt install nfs-common -y
```

- Crie o mesmo novo diretório que será utilizado como ponto de montagem pelo ***node01***, para isso, siga as instruções abaixo:
```shell
sudo mkdir /clusterfs
sudo chown nobody.nogroup -R /clusterfs
sudo chmod 777 -R /clusterfs
```

- Edite o arquivo _/etc/fstab_ e adicione a seguinte linha:
```shell
<master node ip>:/clusterfs    /clusterfs    nfs    defaults   0 0
```
- A linha adicionada deve ficar conforme o exemplo abaixo:
```shell
192.168.0.20:/clusterfs    /clusterfs    nfs    defaults   0 0
```

- Por fim, para que seja possível criar arquivos e compartilhar entre todos os _nodes_, monte a unidade com o comando a seguir:
```shell
sudo mount -a
```

## Troubleshooting
- Visualizar se a pasta compartilhada existe: 
```shell
df -h
```

- Forçar a montagem da pasta compartilhada: 
```shell
mount -t nfs <nfs_server_ip>:<shared_folder_path> <mount_point>
```
