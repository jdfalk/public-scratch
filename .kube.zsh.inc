# Kubernetes
# Pieces taken from https://github.com/ohmyzsh/ohmyzsh/blob/master/plugins/kubectl/kubectl.plugin.zsh

if (( ! $+commands[kubectl] )); then
  return
fi

# If the completion file doesn't exist yet, we need to autoload it and
# bind it to `kubectl`. Otherwise, compinit will have already done that.
if [[ ! -f "$ZSH_CACHE_DIR/completions/_kubectl" ]]; then
  typeset -g -A _comps
  autoload -Uz _kubectl
  _comps[kubectl]=_kubectl
fi

kubectl completion zsh 2> /dev/null >| "$ZSH_CACHE_DIR/completions/_kubectl" &|

# This command is used a LOT both below and in daily life
alias k=kubectl

# Execute a kubectl command against all namespaces
alias kca='_kca(){ kubectl "$@" --all-namespaces;  unset -f _kca; }; _kca'

# Apply a YML file
alias kaf='kubectl apply -f'

# Drop into an interactive terminal on a container
alias keti='kubectl exec -t -i'

# Manage configuration quickly to switch contexts between local, dev ad staging.
alias kcuc='kubectl config use-context'
alias kcsc='kubectl config set-context'
alias kcdc='kubectl config delete-context'
alias kccc='kubectl config current-context'

# List all contexts
alias kcgc='kubectl config get-contexts'

# General aliases
alias kdel='kubectl delete'
alias kdelf='kubectl delete -f'

# Pod management.
alias kgp='kubectl get pods --show-kind'
alias kgpa='kubectl get pods --all-namespaces --show-kind'
alias kgpw='kgp --watch --show-kind'
alias kgpwide='kgp -o wide --show-kind'
alias kep='kubectl edit pods'
alias kdp='kubectl describe pods'
alias kdelp='kubectl delete pods'
alias kgpall='kubectl get pods --all-namespaces -o wide --show-kind'

# get pod by label: kgpl "app=myapp" -n myns
alias kgpl='kgp -l'

# get pod by namespace: kgpn kube-system"
alias kgpn='kgp -n'

# Service management.
alias kgs='kubectl get svc --show-kind'
alias kgsa='kubectl get svc --all-namespaces --show-kind'
alias kgsw='kgs --watch --show-kind'
alias kgswide='kgs -o wide --show-kind'
alias kes='kubectl edit svc'
alias kds='kubectl describe svc'
alias kdels='kubectl delete svc'

# Ingress management
alias kgi='kubectl get ingress --show-kind'
alias kgia='kubectl get ingress --all-namespaces --show-kind'
alias kei='kubectl edit ingress'
alias kdi='kubectl describe ingress'
alias kdeli='kubectl delete ingress'

# Namespace management
alias kgns='kubectl get namespaces --show-kind'
alias kens='kubectl edit namespace'
alias kdns='kubectl describe namespace'
alias kdelns='kubectl delete namespace'
alias kcn='kubectl config set-context --current --namespace'

# ConfigMap management
alias kgcm='kubectl get configmaps --show-kind'
alias kgcma='kubectl get configmaps --all-namespaces --show-kind'
alias kecm='kubectl edit configmap'
alias kdcm='kubectl describe configmap'
alias kdelcm='kubectl delete configmap'

# Secret management
alias kgsec='kubectl get secret --show-kind'
alias kgseca='kubectl get secret --all-namespaces --show-kind'
alias kdsec='kubectl describe secret'
alias kdelsec='kubectl delete secret'

# Deployment management.
alias kgd='kubectl get deployment --show-kind'
alias kgda='kubectl get deployment --all-namespaces --show-kind'
alias kgdw='kgd --watch'
alias kgdwide='kgd -o wide'
alias ked='kubectl edit deployment'
alias kdd='kubectl describe deployment'
alias kdeld='kubectl delete deployment'
alias ksd='kubectl scale deployment'
alias krsd='kubectl rollout status deployment'

function kres(){
  kubectl set env $@ REFRESHED_AT=$(date +%Y%m%d%H%M%S)
}

# Rollout management.
alias kgrs='kubectl get replicaset --show-kind'
alias kdrs='kubectl describe replicaset'
alias kers='kubectl edit replicaset'
alias krh='kubectl rollout history'
alias kru='kubectl rollout undo'

# Statefulset management.
alias kgss='kubectl get statefulset --show-kind'
alias kgssa='kubectl get statefulset --all-namespaces --show-kind'
alias kgssw='kgss --watch --show-kind'
alias kgsswide='kgss -o wide --show-kind'
alias kess='kubectl edit statefulset'
alias kdss='kubectl describe statefulset'
alias kdelss='kubectl delete statefulset'
alias ksss='kubectl scale statefulset'
alias krsss='kubectl rollout status statefulset'

# Port forwarding
alias kpf="kubectl port-forward"

# Tools for accessing all information
alias kga='kubectl get all --show-kind'
alias kgaa='kubectl get all --all-namespaces --show-kind'

# Logs
alias kl='kubectl logs'
alias kl1h='kubectl logs --since 1h'
alias kl1m='kubectl logs --since 1m'
alias kl1s='kubectl logs --since 1s'
alias klf='kubectl logs -f'
alias klf1h='kubectl logs --since 1h -f'
alias klf1m='kubectl logs --since 1m -f'
alias klf1s='kubectl logs --since 1s -f'

# File copy
alias kcp='kubectl cp'

# Node Management
alias kgno='kubectl get nodes --show-kind'
alias keno='kubectl edit node'
alias kdno='kubectl describe node'
alias kdelno='kubectl delete node'

# PVC management.
alias kgpvc='kubectl get pvc --show-kind'
alias kgpvca='kubectl get pvc --all-namespaces --show-kind'
alias kgpvcw='kgpvc --watch --show-kind'
alias kepvc='kubectl edit pvc'
alias kdpvc='kubectl describe pvc'
alias kdelpvc='kubectl delete pvc'

# Service account management.
alias kdsa="kubectl describe sa"
alias kdelsa="kubectl delete sa"

# DaemonSet management.
alias kgds='kubectl get daemonset --show-kind'
alias kgdsa='kubectl get daemonset --all-namespaces --show-kind'
alias kgdsw='kgds --watch --show-kind'
alias keds='kubectl edit daemonset'
alias kdds='kubectl describe daemonset'
alias kdelds='kubectl delete daemonset'

# CronJob management.
alias kgcj='kubectl get cronjob --show-kind'
alias kecj='kubectl edit cronjob'
alias kdcj='kubectl describe cronjob'
alias kdelcj='kubectl delete cronjob'

# Job management.
alias kgj='kubectl get job --show-kind'
alias kej='kubectl edit job'
alias kdj='kubectl describe job'
alias kdelj='kubectl delete job'

# John's Additions

# Basis for other commands
alias kd='kubectl describe'
alias kgwide='kubectl get --output wide --show-kind'
alias kgawide='kga -o wide --show-kind'
alias kgaawide='kgaa -o wide --show-kind'

# Kube config
alias kg='kubectl get --show-kind=true'
alias kcgc='kubectl config get-contexts'

# Editing
alias ke='kubectl edit'
alias kedit='kubectl edit'
alias kexec='kubectl exec -it'

alias kgaaa='kubectl get --all-namespaces --show-kind=true'
alias kgaaawide='kgaaa -o wide'

# Istio Specific 
alias kggatea='kgaaa gateway'
alias kggatewidea='kgaaa gateway -o wide'
alias kgvsa='kgaaa virtualservice'
alias kgavswidea='kgaaa virtualservice -o wide'
alias kgo='kg -o yaml'
alias kgnowide='kubectl get nodes -o wide'

alias ks='kubectl set'
alias ksi='kubectl set image'
alias kannotate='kubectl annotate'

# Original Plugin File to only load aliases if kubectl installed
# Only run if the user actually has kubectl installed
if (( ${+_comps[kubectl]} )); then
  function kj() { kubectl "$@" -o json | jq; }
  function kjx() { kubectl "$@" -o json | fx; }
  function ky() { kubectl "$@" -o yaml | yh; }

  compdef kj=kubectl
  compdef kjx=kubectl
  compdef ky=kubectl
fi
# End of Original Plugin File


# Enable after installing krew
export PATH="${KREW_ROOT:-$HOME/.krew}/bin:$PATH"

function kubectlgetall {
  for i in $(kubectl api-resources --verbs=list --namespaced -o name | grep -v "events.events.k8s.io" | grep -v "events" | sort | uniq); do
    echo "Resource:" $i
    kubectl -n ${1} get --ignore-not-found ${i}
  done
}

function kmerge() {
  KUBECONFIG=~/.kube/config:$1 kubectl config view --flatten > ~/.kube/mergedkub && mv ~/.kube/mergedkub ~/.kube/config
}

# Pod management with image information
alias kgpi='kubectl get pods -o custom-columns="NAME:.metadata.name,READY:.status.containerStatuses[0].ready,STATUS:.status.phase,RESTARTS:.status.containerStatuses[0].restartCount,AGE:.metadata.creationTimestamp,IP:.status.podIP,NODE:.spec.nodeName,IMAGE:.spec.containers[0].image"'

# Random useful things
alias kube-prometheus='kubectl port-forward -n prometheus statefulset.apps/prometheus-prometheus-operator-prometheus 9090:9090'

