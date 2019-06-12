import click
@click.command()
@click.argument('concat')
def cli(concat):
    click.echo(concat)
cli()
