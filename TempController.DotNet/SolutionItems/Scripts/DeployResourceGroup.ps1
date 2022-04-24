param(
    [Parameter()]
    [Description("The name of the resource group to create.")]
    [string]$Name,

    [Parameter()]
    [Description("The location of the resource group.")]
    [string]$Location,
)

Write-Host "Creating resource group $Name in location $Location..."

az group create -n $Name -l $Location

Write-Host "Resource group $Name created."

