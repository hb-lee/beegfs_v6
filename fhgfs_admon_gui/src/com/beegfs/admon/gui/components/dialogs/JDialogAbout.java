package com.beegfs.admon.gui.components.dialogs;

import com.beegfs.admon.gui.common.enums.FilePathsEnum;
import com.beegfs.admon.gui.common.tools.GuiTk;
import com.beegfs.admon.gui.program.Main;
import java.awt.Color;

public class JDialogAbout extends javax.swing.JDialog
{
   private static final long serialVersionUID = 1L;

   private static final int LOGO_WIDHT = 153;
   private static final int LOGO_HEIGHT = 230;

   /**
    * Creates new form JDialogAbout
    */
   public JDialogAbout(java.awt.Frame parent, boolean modal)
   {
      super(parent, modal);
      initComponents();
      jLabelVersion.setText(Main.getVersion());
      this.setBackground(Color.WHITE);
   }

   /**
    * This method is called from within the constructor to initialize the form. WARNING: Do NOT
    * modify this code. The content of this method is always regenerated by the Form Editor.
    */
   @SuppressWarnings("unchecked")
   // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
   private void initComponents()
   {
      java.awt.GridBagConstraints gridBagConstraints;

      jLabelLogo = new javax.swing.JLabel();
      jLabelSupport = new javax.swing.JLabel();
      jLabelITWM = new javax.swing.JLabel();
      jLabelDepartment = new javax.swing.JLabel();
      jButtonClose = new javax.swing.JButton();
      jLabelURL = new javax.swing.JLabel();
      jLabelProduct = new javax.swing.JLabel();
      jLabelVersion = new javax.swing.JLabel();

      setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
      setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
      setResizable(false);
      getContentPane().setLayout(new java.awt.GridBagLayout());

      jLabelLogo.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
      jLabelLogo.setIcon(GuiTk.resizeImage(new javax.swing.ImageIcon(JDialogAbout.class.getResource(FilePathsEnum.IMAGE_BEEGFS_LOGO.getPath())), LOGO_WIDHT, LOGO_HEIGHT));
      jLabelLogo.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
      jLabelLogo.setMaximumSize(new java.awt.Dimension(250, 200));
      jLabelLogo.setMinimumSize(new java.awt.Dimension(230, 153));
      jLabelLogo.setPreferredSize(new java.awt.Dimension(230, 153));
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 0;
      gridBagConstraints.gridy = 0;
      gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
      gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
      gridBagConstraints.weightx = 1.0;
      gridBagConstraints.weighty = 1.0;
      gridBagConstraints.insets = new java.awt.Insets(10, 10, 0, 10);
      getContentPane().add(jLabelLogo, gridBagConstraints);

      jLabelSupport.setText("If you need support please contact support@beegfs.com.");
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 0;
      gridBagConstraints.gridy = 5;
      gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTH;
      gridBagConstraints.insets = new java.awt.Insets(24, 10, 0, 10);
      getContentPane().add(jLabelSupport, gridBagConstraints);

      jLabelITWM.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
      jLabelITWM.setText("BeeGFS is a project of the Fraunhofer ITWM,");
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 0;
      gridBagConstraints.gridy = 3;
      gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTH;
      gridBagConstraints.insets = new java.awt.Insets(24, 10, 0, 10);
      getContentPane().add(jLabelITWM, gridBagConstraints);

      jLabelDepartment.setText("Competence Center for High Performance Computing. ");
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 0;
      gridBagConstraints.gridy = 4;
      gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTH;
      gridBagConstraints.insets = new java.awt.Insets(6, 10, 0, 10);
      getContentPane().add(jLabelDepartment, gridBagConstraints);

      jButtonClose.setText("Close");
      jButtonClose.addActionListener(new java.awt.event.ActionListener()
      {
         public void actionPerformed(java.awt.event.ActionEvent evt)
         {
            jButtonCloseActionPerformed(evt);
         }
      });
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 0;
      gridBagConstraints.gridy = 7;
      gridBagConstraints.ipadx = 348;
      gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
      gridBagConstraints.insets = new java.awt.Insets(24, 10, 10, 10);
      getContentPane().add(jButtonClose, gridBagConstraints);

      jLabelURL.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
      jLabelURL.setText("http://www.beegfs.com");
      jLabelURL.addMouseListener(new java.awt.event.MouseAdapter()
      {
         public void mouseClicked(java.awt.event.MouseEvent evt)
         {
            jLabelURLMouseClicked(evt);
         }
      });
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 0;
      gridBagConstraints.gridy = 6;
      gridBagConstraints.ipadx = 227;
      gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTH;
      gridBagConstraints.insets = new java.awt.Insets(6, 10, 0, 10);
      getContentPane().add(jLabelURL, gridBagConstraints);

      jLabelProduct.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
      jLabelProduct.setText("BeeGFS Admon GUI");
      jLabelProduct.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 0;
      gridBagConstraints.gridy = 1;
      gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTH;
      gridBagConstraints.insets = new java.awt.Insets(12, 10, 0, 10);
      getContentPane().add(jLabelProduct, gridBagConstraints);

      jLabelVersion.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
      jLabelVersion.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
      jLabelVersion.setMaximumSize(new java.awt.Dimension(113, 15));
      jLabelVersion.setMinimumSize(new java.awt.Dimension(113, 15));
      jLabelVersion.setPreferredSize(new java.awt.Dimension(113, 15));
      gridBagConstraints = new java.awt.GridBagConstraints();
      gridBagConstraints.gridx = 0;
      gridBagConstraints.gridy = 2;
      gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTH;
      gridBagConstraints.insets = new java.awt.Insets(6, 10, 0, 10);
      getContentPane().add(jLabelVersion, gridBagConstraints);

      pack();
   }// </editor-fold>//GEN-END:initComponents

    private void jButtonCloseActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonCloseActionPerformed
       dispose();
}//GEN-LAST:event_jButtonCloseActionPerformed

    private void jLabelURLMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jLabelURLMouseClicked

    }//GEN-LAST:event_jLabelURLMouseClicked

   /**
    * @param args the command line arguments
    */
   public static void main(String args[])
   {
      java.awt.EventQueue.invokeLater(new Runnable()
      {

         @Override
         public void run()
         {
            JDialogAbout dialog = new JDialogAbout(new javax.swing.JFrame(), true);
            dialog.addWindowListener(new java.awt.event.WindowAdapter()
            {

               @Override
               public void windowClosing(java.awt.event.WindowEvent e)
               {
                  System.exit(0);
               }
            });
            dialog.setVisible(true);
         }
      });
   }
   // Variables declaration - do not modify//GEN-BEGIN:variables
   private javax.swing.JButton jButtonClose;
   private javax.swing.JLabel jLabelDepartment;
   private javax.swing.JLabel jLabelITWM;
   private javax.swing.JLabel jLabelLogo;
   private javax.swing.JLabel jLabelProduct;
   private javax.swing.JLabel jLabelSupport;
   private javax.swing.JLabel jLabelURL;
   private javax.swing.JLabel jLabelVersion;
   // End of variables declaration//GEN-END:variables
}
