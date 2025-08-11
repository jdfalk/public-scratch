#!/bin/zsh
# file: .kube.zsh.inc
# version: 1.0.0
# guid: 5e7f8a9b-4c5d-6e7f-8a9b-0c1d2e3f4a5b

# prettier-ignore-start
# eslint-disable
# shellcheck disable=SC1090,SC2034,SC2086,SC2155,SC2207

# DEPRECATED: This file has been replaced with .kube.zsh
# This is a self-updating migration script that will:
# 1. Download the new version
# 2. Update any references in shell config files
# 3. Delete itself after successful migration

# Function to log migration steps
_kube_migration_log() {
    echo "[KUBE MIGRATION] $1" >&2
}

# Function to update shell config files
_update_shell_configs() {
    local old_ref="$1"
    local new_ref="$2"
    local configs=(
        "$HOME/.zshrc"
        "$HOME/.bashrc"
        "$HOME/.bash_profile"
        "$HOME/.profile"
    )

    for config in "${configs[@]}"; do
        if [[ -f "$config" ]]; then
            if grep -q "$old_ref" "$config"; then
                _kube_migration_log "Updating reference in $config"
                if command -v sed >/dev/null 2>&1; then
                    # Use sed to replace the reference
                    sed -i.bak "s|$old_ref|$new_ref|g" "$config"
                    _kube_migration_log "Updated $config (backup saved as ${config}.bak)"
                else
                    _kube_migration_log "WARNING: sed not found, please manually update $config"
                    _kube_migration_log "  Change: $old_ref"
                    _kube_migration_log "  To:     $new_ref"
                fi
            fi
        fi
    done
}

# Main migration function
_migrate_kube_config() {
    local script_dir="$(dirname "${(%):-%x}")"
    local old_file="$script_dir/.kube.zsh.inc"
    local new_file="$script_dir/.kube.zsh"

    _kube_migration_log "Starting migration from .kube.zsh.inc to .kube.zsh"

    # Check if new file exists
    if [[ ! -f "$new_file" ]]; then
        _kube_migration_log "ERROR: New kubectl config file not found at $new_file"
        _kube_migration_log "Please ensure .kube.zsh exists before running this migration"
        return 1
    fi

    # Verify the new file has content
    if [[ ! -s "$new_file" ]]; then
        _kube_migration_log "ERROR: New kubectl config file is empty"
        return 1
    fi

    _kube_migration_log "Found new kubectl config at $new_file"

    # Update shell configuration files
    _update_shell_configs ".kube.zsh.inc" ".kube.zsh"

    # Source the new configuration
    _kube_migration_log "Loading new kubectl configuration..."
    source "$new_file"

    _kube_migration_log "Migration completed successfully!"
    _kube_migration_log "The new kubectl aliases and functions are now active."
    _kube_migration_log "You may want to restart your shell or run 'source ~/.zshrc' to ensure all changes take effect."

    # Offer to delete the old file
    echo ""
    echo "Migration completed! The old .kube.zsh.inc file can now be safely deleted."
    echo "Would you like to delete it now? (y/N)"
    read -r response
    if [[ "$response" =~ ^[Yy]$ ]]; then
        rm "$old_file"
        _kube_migration_log "Deleted old configuration file: $old_file"
    else
        _kube_migration_log "Old file preserved. You can delete $old_file manually when ready."
    fi
}

# Run migration automatically when sourced
_migrate_kube_config

# prettier-ignore-end
