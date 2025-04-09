#!/bin/bash
#SBATCH -Jtrain         # Job name
#SBATCH -N1 --ntasks-per-node=4          # Number of nodes and cores per node required
#SBATCH -GA40
#SBATCH --mem-per-gpu=40GB
#SBATCH -t60                             # Duration of the job (Ex: 15 mins)
#SBATCH -oReport-%j.out                  # Combined output and error messages file
#SBATCH --mail-type=BEGIN,END,FAIL       # Mail preferences
#SBATCH --mail-user=youj2005@gatech.edu # E-mail address for notifications
cd $SLURM_SUBMIT_DIR                     # Change to working directory

module load anaconda3                    # Load module dependencies
conda init
conda activate nest
srun python img_reconstruct_train.py                  