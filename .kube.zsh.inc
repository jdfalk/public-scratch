# Kubernetes
function kmerge() {
  KUBECONFIG=~/.kube/config:$1 kubectl config view --flatten > ~/.kube/mergedkub && mv ~/.kube/mergedkub ~/.kube/config
}
alias kube-prometheus='kubectl port-forward -n prometheus statefulset.apps/prometheus-prometheus-operator-prometheus 9090:9090'
alias kcgc='kubectl config get-contexts'
alias kcuc='kubectl config use-context'
alias kd='kubectl describe'
alias kdrain='kubectl drain --ignore-daemonsets'
alias kds='kubectl describe -n kube-system'
alias ke='kubectl edit'
alias kedit='kubectl edit'
alias kexec='kubectl exec -it'
alias kg='kubectl get --show-kind=true'
alias kga='kg --all-namespaces'
alias kgaa='kga all'
alias kgaaw='kga all -o wide'
alias kgad='kga deployments'
alias kgadw='kga deployments -o wide'
alias kgagate='kga gateway'
alias kgagatew='kga gateway -o wide'
alias kgap='kga pods'
alias kgapw='kga pods -o wide'
alias kgas='kga services'
alias kgasw='kga services -o wide'
alias kgavs='kga virtualservice'
alias kgavsw='kga virtualservice -o wide'
alias kgo='kg -o yaml'
alias kgksa='kga all'
alias kgksaw='kg --namespace kube-system all -o wide'
alias kgn='kubectl get nodes'
alias kgnw='kubectl get nodes -o wide'
alias kgna='kg all'
alias kgna-istio='kgna -n istio-system'
alias kgnaw='kg all -o wide'
alias kgs='kg -n kube-system'
alias kgp='kg pods'
alias kl='kubectl logs'
alias kls='kubectl logs -n kube-system'
alias krs='kubectl rollout status'
alias ks='kubectl set'
alias ksi='kubectl set image'



### BEGIN ISTIO ###
# Istio
# Port forward to the first istio-ingressgateway pod
alias igpf='kubectl -n istio-system port-forward $(kubectl -n istio-system get pods -listio=ingressgateway -o=jsonpath="{.items[0].metadata.name}") 15000:15000'

# Get the http routes from the port-forwarded ingressgateway pod (requires jq)
alias iroutes='curl --silent http://localhost:15000/config_dump | jq '\''.configs.routes.dynamic_route_configs[].route_config.virtual_hosts[] | {name: .name, domains: .domains, route: .routes[].match.prefix}'\'''

# Get the logs of the first istio-ingressgateway pod
# Shows what happens with incoming requests and possible errors
alias igl='kubectl -n istio-system logs $(kubectl -n istio-system get pods -l istio=ingressgateway -o=jsonpath="{.items[0].metadata.name}") -c istio-proxy --tail=300'

# Get the logs of the first istio-pilot pod
# Shows issues with configurations or connecting to the Envoy proxies
alias ipl='kubectl -n istio-system logs $(kubectl -n istio-system get pods -l istio=pilot -o=jsonpath="{.items[0].metadata.name}")  discovery --tail=300'

# Grab proxy config
alias istgpc='istioctl proxy-config cluster -n istio-system $(kubectl -n istio-system get pods -listio=ingressgateway -o=jsonpath="{.items[0].metadata.name}")'

### END ISTIO ###