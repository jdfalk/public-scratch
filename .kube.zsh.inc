# Kubernetes
# Pieces taken from 

if (( $+commands[kubectl] )); then
    __KUBECTL_COMPLETION_FILE="${ZSH_CACHE_DIR}/kubectl_completion"

    if [[ ! -f $__KUBECTL_COMPLETION_FILE ]]; then
        kubectl completion zsh >! $__KUBECTL_COMPLETION_FILE
    fi

    [[ -f $__KUBECTL_COMPLETION_FILE ]] && source $__KUBECTL_COMPLETION_FILE

    unset __KUBECTL_COMPLETION_FILE
fi


function kmerge() {
  KUBECONFIG=~/.kube/config:$1 kubectl config view --flatten > ~/.kube/mergedkub && mv ~/.kube/mergedkub ~/.kube/config
}

# Random useful things
alias kube-prometheus='kubectl port-forward -n prometheus statefulset.apps/prometheus-prometheus-operator-prometheus 9090:9090'

# This command is used a LOT both below and in daily life
alias k=kubectl

# Basis for other commands
alias kg='kubectl get --show-kind=true'
alias kd='kubectl describe'



# Kube config
alias kcgc='kubectl config get-contexts'
alias kcuc='kubectl config use-context'


# Pods
alias kgp='kg pods'
alias kgpwide='kg pods -o wide'
alias kgap='kga pods'
alias kgapwide='kga pods -o wide'

# Services
alias kgas='kga services'
alias kgaswide='kga services -o wide'
alias kgs='kg services'
alias kgswide='kg services -o wide'



alias kdrain='kubectl drain --ignore-daemonsets'
alias kds='kubectl describe -n kube-system'
alias ke='kubectl edit'
alias kedit='kubectl edit'
alias kexec='kubectl exec -it'

alias kga='kg --all-namespaces'
alias kgawide='kga -o wide'
alias kgaa='kga all'
alias kgaawide='kga all -o wide'
alias kgad='kga deployments'
alias kgadwide='kga deployments -o wide'
alias kgagate='kga gateway'
alias kgagatewide='kga gateway -o wide'


alias kgavs='kga virtualservice'
alias kgavswide='kga virtualservice -o wide'
alias kgo='kg -o yaml'
alias kgksa='kga all'
alias kgksawide='kg --namespace kube-system all -o wide'
alias kgn='kubectl get nodes'
alias kgnwide='kubectl get nodes -o wide'
alias kgna='kg all'
alias kgna-istio='kgna -n istio-system'
alias kgnawide='kg all -o wide'


alias kl='kubectl logs'
alias kls='kubectl logs -n kube-system'
alias krs='kubectl rollout status'
alias ks='kubectl set'
alias ksi='kubectl set image'
alias kannotate='kubectl annotate'



